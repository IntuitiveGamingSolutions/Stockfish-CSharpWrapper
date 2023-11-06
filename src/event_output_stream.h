#ifndef EVENT_OUTPUT_STREAM_H
#define EVENT_OUTPUT_STREAM_H

#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <type_traits>

class EventOutputStream {
public:
	using OutputReceivedCallback = std::function<void(const char*)>;
	
	// Constructor(s)
	EventOutputStream() = default;
	EventOutputStream(OutputReceivedCallback callback) {
        outputCallback = callback;
    }
	
	// Public method(s).
	void set_output_callback(const OutputReceivedCallback& callback) { outputCallback = callback; }
	
	// Public type-specific overload(s).
	EventOutputStream& operator<<(const char* val) {
		// Invoke the 'on output received' callback.
		on_output_received(val);
		
		// Forward the output to cout.
		std::cout << val;	
		return *this;
	}
	
	EventOutputStream& operator<<(const std::string& val) {
		// Invoke the 'on output received' callback.
		on_output_received(val.c_str());
		
		// Forward the output to cout.
		std::cout << val;	
		return *this;
	}
	
	// Public template overload(s).
	template<typename T>
	EventOutputStream& operator<<(const T& val) {
		// Forward the output to cout.
		std::cout << val;
		return *this;
	}
		
	EventOutputStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
        // Call the manipulator to modify the stream (e.g., std::endl)
        manip(std::cout);
        return *this;
    }
private:
	// Private field(s).
	OutputReceivedCallback outputCallback;

	// Private callback(s).
    void on_output_received(const char* output) {
        if (outputCallback) {
            outputCallback(output);
        }
    } 
};
#endif
