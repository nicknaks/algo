
//#include "Huffman.h"
typedef unsigned char byte;
#define interface struct
interface IInputStream {
  // Возвращает false, если поток закончился
  virtual bool Read(byte& value) = 0;
};
interface IOutputStream {
  virtual void Write(byte value) = 0;
};

class Huffman{
 public:
  Huffman(){
    frequency.resize(256);
    code.resize(256);
  }

 private:
  std::vector<int> frequency;
  std::vector<std::vector<unsigned char >> code;
};

class BitReader{

 public:
  BitReader();
  void WriteBit(byte bit);
  void WriteByte(byte bit);
 private:
  std::vector<byte> buffer;
  int bitsCount;
};


int main(){

}


static void copyStream(IInputStream& input, IOutputStream& output) {
  byte value;
  while(input.Read(value)) { output.Write(value); }
}

void Encode(IInputStream& original, IOutputStream& compressed) {
  copyStream(original, compressed);
}

void Decode(IInputStream& compressed, IOutputStream& original) {
  copyStream(compressed, original);
}