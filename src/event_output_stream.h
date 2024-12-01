#ifndef EVENT_OUTPUT_STREAM_H
#define EVENT_OUTPUT_STREAM_H

#include "uci.h"

#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <type_traits>

class EventOutputStream {
public:
	using OutputReceivedCallback = std::function<void(const char*)>;
	
	// Constructor(s)
	EventOutputStream() : outputCallback(nullptr) {}
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
	
	EventOutputStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
        // Call the manipulator to modify the stream (e.g., std::endl)
        manip(std::cout);
        return *this;
    }
	
	// Public custom type overload(s).
	EventOutputStream& operator <<(const Stockfish::UCI::OptionsMap& val) {
		for (size_t idx = 0; idx < val.size(); ++idx) // Done in this way to enforce UCI index rules.
		{
			for (const auto& it : val)
			{
				if (it.second.get_idx() == idx)
				{
					const Stockfish::UCI::Option& o = it.second;
					on_output_received(o.get_option_string(it.first).c_str());
					break;
				}
			}
		}
		
		return *this;
	}
	
	// Public template overload(s).
	template <typename T, typename std::enable_if_t<std::is_integral_v<T>, int> = 0>
    EventOutputStream& operator<<(const T& val) {
        // Invoke the 'on output received' callback.
        on_output_received(std::to_string(val).c_str());

        // Forward the output to cout.
        std::cout << val;

        return *this;
    }

    template <typename T, typename std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
    EventOutputStream& operator<<(const T& val) {
        // Invoke the 'on output received' callback.
        on_output_received(std::to_string(val).c_str());

        // Forward the output to cout.
        std::cout << val;

        return *this;
    }
	
	template <typename T, typename std::enable_if_t<std::is_convertible_v<T, std::string>, int> = 0>
    EventOutputStream& operator<<(const T& val) {
        // Invoke the 'on output received' callback.
        on_output_received(std::to_string(val).c_str());

        // Forward the output to cout.
        std::cout << val;

        return *this;
    }

    template <typename T, typename std::enable_if_t<!std::is_convertible_v<T, std::string> && !std::is_integral_v<T> && !std::is_floating_point_v<T>, int> = 0>
    EventOutputStream& operator<<(const T& val) {
        // Forward the output to cout.
        std::cout << val;

        return *this;
    }
private:
	// Private field(s).
	OutputReceivedCallback outputCallback;

	// Private callback(s).
    void on_output_received(const char* output) {
        if (outputCallback != nullptr) {
            outputCallback(output);
        }
    } 
};
#endif
