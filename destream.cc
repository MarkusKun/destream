#include <fstream>
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]){
  using std::cout; using std::endl; using std::cerr;
  std::string inputFilename = "SONG.RAW"; // take from arguments, later?

  std::string inFile;
  cout << "Reading: " << inputFilename << endl;
  { // read input file
    std::ifstream inStream;
    inStream.open(inputFilename.c_str());
    if (!inStream.is_open()){
      cerr << "Error opening " << inputFilename << endl;
      inStream.close();
      exit(EXIT_FAILURE);
    }
    unsigned int dataCounter=0;
    while (!inStream.eof()){
      char readChar;
      inStream.get ( readChar );
      inFile+=readChar;
      dataCounter++;
    }
    inStream.close();
    cout << dataCounter << " bytes read" << endl;
  }
  unsigned int sourceFileSize = inFile.size();
  cout << "String contains " << sourceFileSize << " chars" << endl;
  
  std::ofstream outStream1;
  std::ofstream outStream2;
  { // open output streams
    outStream1.open("out1.RAW");
    outStream2.open("out2.RAW");
    if (
      (!outStream1.is_open()) ||
      (!outStream2.is_open())
      )
    {
      cerr << "error opening output files for writing" << endl;
      outStream1.close();
      outStream2.close();
      exit(EXIT_FAILURE);
    }
  }
  unsigned int samplesPerChunk=24585;
  unsigned int chunkSize=4*samplesPerChunk; // 131072; // try one kilo
  unsigned int getChunkSize = 2*chunkSize;
  unsigned int chunkOffset=3*chunkSize; // start of chunk vs start of next chunk
  unsigned int startOffset=0*chunkSize;
  { // extracting
    unsigned int currentOffset;
    for (
      currentOffset  = startOffset;
      currentOffset  < sourceFileSize;
      currentOffset += chunkOffset
      )
    {
      std::string currentChunk = inFile.substr(currentOffset,getChunkSize);
      std::cout << "0x" << std::hex << currentOffset << " -> 0x" << currentOffset+getChunkSize-1 << std::endl;
      outStream1 << currentChunk;
    }
  }
  outStream1.close();
  outStream2.close();
  
  return 0;
}
  
  
  
