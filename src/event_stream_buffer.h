#ifndef EVENT_STREAM_BUFFER_H
#define EVENT_STREAM_BUFFER_H

#include <functional>
#include <vector>
#include <iostream>
#include <streambuf>
#include <string>
#include <sstream>

class EventStreamBuffer : public std::streambuf {
public:
	using OutputReceivedCallback = std::function<void(const char*, const char*)>;
    EventStreamBuffer(OutputReceivedCallback callback) : outputCallback(callback) {
        // Set the buffer size as needed.
        buffer.resize(1024);
        setp(&buffer[0], &buffer[0] + buffer.size());
    }

    int_type overflow(int_type c = traits_type::eof()) override {
        // Process the buffer content by invoking the callback.
        on_output_received(pbase(), pptr());

        // Reset the buffer
        setp(&buffer[0], &buffer[0] + buffer.size());
        
        if (c != traits_type::eof()) {
            // If c is not EOF, put it to the buffer
            *pptr() = c;
            pbump(1);
        }

        return traits_type::not_eof(c);
    }
	
	void redirect_output() {
		std::cout.rdbuf(this);
	}

private:
    void on_output_received(const char* begin, const char* end) {
        if (outputCallback) {
            outputCallback(begin, end);
        }
    }

    std::vector<char> buffer;
    OutputReceivedCallback outputCallback;
};
#endif
