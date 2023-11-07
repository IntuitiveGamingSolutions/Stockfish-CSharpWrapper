#ifndef STOCKFISH_WRAPPER_H
#define STOCKFISH_WRAPPER_H

#include <cstddef>
#include <iostream>

#include "export.h"

namespace StockfishWrapper {
    // SECTION: Stockfish core method(s).
	extern "C" DLL_API bool is_initialized();
    extern "C" DLL_API void initialize();
    extern "C" DLL_API void deinitialize();
	
	// SECTION: cout redirection.
	typedef void (*LineProcessedDelegate)(const char* line);
	extern "C" DLL_API void register_output_line_callback(LineProcessedDelegate callback);
    
    // SECTION: Stockfish UCI wrapper.
    namespace UCI {
        extern "C" DLL_API void process_command(const char* cmd);
    }
}

#endif
