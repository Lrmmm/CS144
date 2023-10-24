#include <stdexcept>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : 
  capacity_( capacity ), 
  buffer_(""), 
  closed_(false),
  error_(false),
  pushedBytes_(0),
  popedBytes_(0),
  buffer_size_(0)
    {}

void Writer::push( string data )
{
  // Your code here.
  (void)data;

  uint64_t write_size = capacity_ - buffer_size_ >= data.size() ? data.size() : capacity_ - buffer_size_;
  buffer_ += data.substr(0, write_size);
  pushedBytes_ += write_size;
  buffer_size_ += write_size;

}

void Writer::close()
{
  // Your code here.
  closed_ = true;
}

void Writer::set_error()
{
  // Your code here.
  error_ = true;
}

bool Writer::is_closed() const
{
  // Your code here.
  return {closed_};
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return {capacity_ - buffer_size_};
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return {pushedBytes_};
}

string_view Reader::peek() const
{
  // Your code here.
  return buffer_;
}

bool Reader::is_finished() const
{
  // Your code here.
  return bytes_buffered() == 0 && closed_;
}

bool Reader::has_error() const
{
  // Your code here.
  return error_;
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  buffer_ = buffer_.erase(0,len);
  popedBytes_ += len;
  buffer_size_ -= len;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return buffer_size_;
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return  popedBytes_;
}
