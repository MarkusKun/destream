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
  unsigned int sourceFileSize = inFile.size()-1;
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
  unsigned int samplesPerChunk=24576;
  unsigned int chunkSize=4*samplesPerChunk; 
  unsigned int getChunkSize1 = 2*chunkSize;
  unsigned int getChunkSize2 = 1*chunkSize;
  unsigned int startOffset=0*chunkSize;
  { // extracting
    unsigned int currentOffset=startOffset;
    while (currentOffset < sourceFileSize){
      cout << " " << std::dec << currentOffset;
      cout << " -> " << std::dec << currentOffset+getChunkSize1-1 << std::flush;
      std::string currentChunk1 = inFile.substr(currentOffset,getChunkSize1);
      outStream1 << currentChunk1;
      currentOffset += getChunkSize1;

      cout << " " << currentOffset;
      cout << " -> " << std::dec << currentOffset+getChunkSize2-1 << std::endl;
      std::string currentChunk2 = inFile.substr(currentOffset,getChunkSize2);
      outStream2 << currentChunk2;
      currentOffset += getChunkSize2;
    }
  }
  outStream1.close();
  outStream2.close();
  
  return 0;
}
  
  
  
