#include <stdlib.h>
#include <iostream>
#include <boost/optional/optional_io.hpp>
#include <boost/optional.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "snark.hpp"
#include "utils.cpp"

using namespace libsnark;
using namespace std;

int genProof(r1cs_ppzksnark_proving_key<default_r1cs_ppzksnark_pp> provingKey_in, string proofFileName, string publicInputs, string privateInputs)
{
  // Initialize bit_vectors for all of the variables involved.
  vector<bool> h_startBalance_bv(256);
  vector<bool> h_endBalance_bv(256);
  vector<bool> h_incoming_bv(256);
  vector<bool> h_outgoing_bv(256);
  vector<bool> r_startBalance_bv(256);
  vector<bool> r_endBalance_bv(256);
  vector<bool> r_incoming_bv(256);
  vector<bool> r_outgoing_bv(256);

  vector<vector<unsigned long int>> publicValues = fillValuesFromfile(publicInputs);
  h_startBalance_bv = int_list_to_bits_local(publicValues[0], 8);
  h_endBalance_bv = int_list_to_bits_local(publicValues[1], 8);
  h_incoming_bv = int_list_to_bits_local(publicValues[2], 8);
  h_outgoing_bv = int_list_to_bits_local(publicValues[3], 8);

  vector<vector<unsigned long int>> privateValues = fillValuesFromfile(privateInputs);
  r_startBalance_bv = int_list_to_bits_local(privateValues[0], 8);
  r_endBalance_bv = int_list_to_bits_local(privateValues[1], 8);
  r_incoming_bv = int_list_to_bits_local(privateValues[2], 8);
  r_outgoing_bv = int_list_to_bits_local(privateValues[3], 8);

  cout << "Starting proof generation for " + proofFileName << endl;
  boost::optional<libsnark::r1cs_ppzksnark_proof<libff::alt_bn128_pp>> proof = generate_payment_in_out_proof<default_r1cs_ppzksnark_pp>(provingKey_in, h_startBalance_bv, h_endBalance_bv, h_incoming_bv, h_outgoing_bv, r_startBalance_bv, r_endBalance_bv, r_incoming_bv, r_outgoing_bv);

  if(proof == boost::none)
  {
    return 1;
  } else {
    stringstream proofStream;
    proofStream << proof;

    ofstream fileOut;
    fileOut.open(proofFileName);

    fileOut << proofStream.rdbuf();
    fileOut.close();
    cout << "Proof was generated!!" << proofFileName << endl;
    return 0;
  }
}

int getUserInput(r1cs_ppzksnark_proving_key<default_r1cs_ppzksnark_pp> provingKey_in)
{
  string inputTemp = "";
  int result=0;
  cout << "Press enter paymentId to generate a proof or q to quit" << endl;
  cin >> inputTemp;  
  cout << "Input from console: " << inputTemp << endl;
  if(inputTemp != "q")
  {
    string proofName = "proof_single_";
    string proofNameWithId = proofName + inputTemp;
    string publicInputs = "publicInputParameters_single_";
    string publicInputsWithId = publicInputs + inputTemp;
    string privateInputs = "privateInputParameters_single_";
    string privateInputsWithId = privateInputs + inputTemp;

    cout << proofNameWithId << endl;
    result = genProof(provingKey_in, proofNameWithId, publicInputsWithId, privateInputsWithId);
    if(result!=0)
    {
      cout << "There was an error generating the proof" << endl;
      return getUserInput(provingKey_in);
    }
    else
    {
      return getUserInput(provingKey_in);
    }
  }
  else
  {
    return 0;
  }
}


int main(int argc, char *argv[])
{
  string keyFileName = "provingKey_single";

  // Initialize the curve parameters.
  default_r1cs_ppzksnark_pp::init_public_params();

  r1cs_ppzksnark_proving_key<default_r1cs_ppzksnark_pp> provingKey_in;

  ifstream fileIn(keyFileName);
  stringstream provingKeyFromFile;
  if (fileIn) {
     provingKeyFromFile << fileIn.rdbuf();
     fileIn.close();
  }
 
  provingKeyFromFile >> provingKey_in;
 
  return getUserInput(provingKey_in);
}
