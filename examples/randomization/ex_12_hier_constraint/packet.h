// nbcode "packet" start
struct packet_t {
  sc_uint<32> src_addr;
  sc_uint<32> dest_addr;
  sc_uint<16> msg_length;
  char        msg[1024];
};
// nbcode "packet" end

// nbcode "out" start
//define an ostream for a packet object
ostream& operator<<(ostream& os, const packet_t& p) {
  os << "{\n"
     << "   src_addr: " << p.src_addr << "\n"
     << "   dest_addr: " << p.dest_addr << "\n"
     << "   msg_length: " << p.msg_length << "\n"
     << "   msg {\n"
     << "     " << p.msg  << "\n"
     << "   }\n}" << endl;
  return os;
}
// nbcode "out" end

