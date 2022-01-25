# ZeroKnowledgeProofs
Zero Knowledge Proof
Zero Knowledge Proofs and how they can be implemented in Quorum

This is a SNARK implementation using libsnark for the following:

ZkPoK{ (R1, R2, R3): Hi = sha256(Ri) and R3 = R1 + R2 }

Read: given H1, H2, H3, prove you know R1, R2, R3 such that R1 is the preimage of H1, R2 is the preimage of H2, R3 is the preimage of H3, and R3 is R1 + R2.




howto
Required packages
On Ubuntu 16.04 LTS:

  `$ sudo apt-get install build-essential cmake git libgmp3-dev libprocps4-dev python-markdown libboost-all-dev libssl-dev`
On Ubuntu 14.04 LTS:

  `$ sudo apt-get install build-essential cmake git libgmp3-dev libprocps3-dev python-markdown libboost-all-dev libssl-dev`
Installation
./get-libsnark && make

npm install

Running
node index.js startBalance=10000

First select

Single payment in and single payment out
Multiple payments in and multiple payments out
Follow the prompts.

Generate a key pair
Generate a proof (single or multiple)
Verify proof
Quit
Generate a new key pair
This creates a new proving key and verification key from the circuit. They are saved to the files:

provingKey-single or provingKey-multi
verificationKey-single or verificationKey-multi
Generate a payment proof
This generates a proof using the proving key as well as the following values:

start balance
incoming payment/s
outgoing payment/s
end balance (start balance + incoming - outgoing)
The proof is:

start balance + incoming payments = end balance + outgoing payments
Verify payment proof
Verifies the above proofs
