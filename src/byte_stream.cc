#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

void Writer::push( string data )
{
  auto pushed = min( data.size(), available_capacity() );
  sum_bytes_pushed += pushed;
  buffer_.append( data.substr( 0, pushed ) );
}

void Writer::close()
{
  buffer_is_closed = true;
}

bool Writer::is_closed() const
{
  return buffer_is_closed;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer_.size();
}

uint64_t Writer::bytes_pushed() const
{
  return sum_bytes_pushed;
}

string_view Reader::peek() const
{
  return string_view( buffer_.data(), buffer_.size() );
}

void Reader::pop( uint64_t len )
{
  auto poped = min( len, buffer_.size() );
  sum_bytes_poped += poped;
  buffer_.erase( 0, poped );
}

bool Reader::is_finished() const
{
  return buffer_is_closed && buffer_.empty();
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.size();
}

uint64_t Reader::bytes_popped() const
{
  return sum_bytes_poped;
}
