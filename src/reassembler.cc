#include "reassembler.hh"
#include <algorithm>
using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{
  // Your code here.
  if (_init_flag) {
    _reassembleBuf.resize(output.available_capacity(), 0);
    _flagBuf.resize(output.available_capacity(), 0);
    _init_flag = 0;
  }

  if (is_last_substring)
    _endIndex = first_index + data.size();
  
  _first_unassembled_index = output.bytes_pushed();
  _first_unacceptable_index = _first_unassembled_index + output.available_capacity();

  uint64_t str_begin;
  uint64_t str_end;

  if (!data.empty()) {
    if (first_index + data.size() < _first_unassembled_index || first_index >= _first_unacceptable_index){
      data = "";
    }
    else {
      str_begin = first_index;
      str_end = str_begin + data.size() - 1;
      if (first_index < _first_unassembled_index)
        str_begin = _first_unassembled_index;
      if(first_index + data.size() > _first_unacceptable_index)
        str_end = _first_unacceptable_index - 1;
      for (uint64_t i = str_begin; i <= str_end; i++) {
        _reassembleBuf[i - _first_unassembled_index] = data[i - first_index];
        _flagBuf[i - _first_unassembled_index] = true;
      }
    }
  }

  string tmp;
  while (_flagBuf.front() == true) {
    tmp += _reassembleBuf.front();
    _reassembleBuf.pop_front();
    _flagBuf.pop_front();
    _reassembleBuf.push_back(0);
    _flagBuf.push_back(0);

  }
  output.push(tmp);

  if (output.bytes_pushed() == _endIndex)
    output.close();
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return static_cast<uint64_t>(count(_flagBuf.begin(),_flagBuf.end(),true));
}


Reassembler::Reassembler() : 
  _first_unassembled_index(0), 
  _first_unacceptable_index(0),
  _reassembleBuf(),
  _flagBuf(),
  _endIndex(-1),
  _init_flag(1)
{}

