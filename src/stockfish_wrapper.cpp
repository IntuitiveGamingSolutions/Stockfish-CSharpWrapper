#include "stockfish_wrapper.h"
#include "uci.h"
#include "misc.h"
#include "tune.h"
#include "types.h"
#include "thread.h"
#include "search.h"
#include "bitboard.h"
#include "position.h"
#include "evaluate.h"
#include "event_out.h"
#include <iostream>

namespace StockfishWrapper {
	// Static (local) field(s).
	static LineProcessedDelegate outputLineCallback = nullptr;
	static bool isInitialized = false;
	
	// Static (local) callback(s).
	static void on_output_received(const char* output) {
		if (outputLineCallback) {
			outputLineCallback(output);
		}
	}
	
	// IMPLEMENTATION: StockfishWrapper
	bool is_initialized() {
		return isInitialized;
	}
	
	void initialize() {
		// Redirect cout.
		IO::set_event_out_callback(on_output_received);

		// Log engine version.
		IO::event_out << Stockfish::engine_info() << std::endl;
		
		// Initialize.
		Stockfish::UCI::init(Stockfish::Options);
		Stockfish::Tune::init();
		Stockfish::Bitboards::init();
		Stockfish::Position::init();
		Stockfish::Threads.set(size_t(Stockfish::Options["Threads"]));
		Stockfish::Search::clear();  // After threads are up
		Stockfish::Eval::NNUE::init();	

		// Start a new game.
		Stockfish::UCI::new_game();
		
		// Initialized.
		isInitialized = true;
	}

	void deinitialize() {
		Stockfish::Threads.set(0);
		
		// Not initialized.
		isInitialized = false;
	}
	
	void register_output_line_callback(LineProcessedDelegate callback) {
		outputLineCallback = callback;
	}
	
	namespace UCI {
		void process_command(const char* cmd) {
			Stockfish::UCI::process_command(cmd);
		}
	}
}
