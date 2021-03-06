#ifndef CHAT_PACKET_HPP
#define CHAT_PACKET_HPP
#include <cstdio>
#include <cstdlib>
#include <cstring>
//need more readability to enum
enum Operation{ Log_in='a', Login_fail, Hash, Room_list, In_room, Out_room, Message, Log_out, None };
class chat_packet{
	public:
		enum { header_length = 4 };
		enum { max_body_length = 512 };
		chat_packet()
			: body_length_(0){
		}
		const char* data() const{
			return data_;
		}
		char* data(){
			return data_;
		}
		std::size_t length() const{
			return header_length + body_length_;
		}
		const char* body() const{
			return data_ + header_length;
		}
		char* body(){
			return data_ + header_length;
		}
		std::size_t body_length() const{
			return body_length_;
		}
		void body_length(std::size_t new_length){
			body_length_ = new_length;
			if(body_length_ > max_body_length)
				body_length_ = max_body_length;
		}
		void write(std::string header_,std::string body_){
			if(header_.size() + body_.size() > max_body_length+header_length)
				return;
			header_.copy(data_,4);
			data_[header_.size()]='\0';
			body_.copy(data_+4,body_.size());
			body_length(body_.size());
			data_[body_.size()+4]='\0';
		}
		int decode_header(){
			std::cout << "Decode Header" << std::endl;
			char header[header_length+1] = "";
			std::strncat(header,data_,header_length);
			body_length_ = std::atoi(&(header[1]));
			std::cout << std::string(header,header_length) << body_length_ << std::endl;
			if(body_length_ > max_body_length){
				body_length_ = 0;
				return Operation::None;
			}
			switch(header[0]){
				case Operation::Log_in :
					return Operation::Log_in;
				case Operation::Login_fail:
					return Operation::Login_fail;
				case Operation::Hash :
					return Operation::Hash;
				case Operation::Room_list :
					break;
				case Operation::In_room :
					break;
				case Operation::Out_room:
					break;
				case Operation::Message:
					break;
				case Operation::Log_out:
					break;
			}
			return Operation::None;
		}
		void encode_header(){
			char header[header_length+1] = "";
			std::sprintf(header,"%4d",static_cast<int>(body_length_));
			std::memcpy(data_,header,header_length);
		}
		void print(){
			std::cout << std::string(data_,this->length()) << std:: endl;
		}
	private:
		char data_[header_length + max_body_length ];
		size_t body_length_;
};
#endif
