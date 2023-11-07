#ifndef STOCKFISH_WRAPPER_H
#define STOCKFISH_WRAPPER_H

#include <cstddef>
#include <iostream>

namespace StockfishWrapper {
    // SECTION: Stockfish core method(s).
	extern "C" __declspec(dllexport) bool is_initialized();
    extern "C" __declspec(dllexport) void initialize();
    extern "C" __declspec(dllexport) void deinitialize();
	
	// SECTION: cout redirection.
	typedef void (*LineProcessedDelegate)(const char* line);
	extern "C" __declspec(dllexport) void register_output_line_callback(LineProcessedDelegate callback);
    
    // SECTION: Stockfish UCI wrapper.
    namespace UCI {
        extern "C" __declspec(dllexport) void process_command(const char* cmd);
    }
}

#endif
