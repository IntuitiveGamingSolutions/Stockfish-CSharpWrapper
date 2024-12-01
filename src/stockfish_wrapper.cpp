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
	static bool isUciInitialized = false;
	
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
		
		// Initialize UCI if it isnt.
		if (!is_uci_initialized())
			initialize_uci();
		
		// Initialize.
		Stockfish::Tune::init();
		Stockfish::Bitboards::init();
		Stockfish::Position::init();
		Stockfish::Threads.set(size_t(Stockfish::Options["Threads"]));
		Stockfish::Search::clear();  // After threads are up
		
		// Initialize NNUE.
		Stockfish::Eval::NNUE::init();	

		// Start a new game.
		Stockfish::UCI::new_game();
		
		// Initialized.
		isInitialized = true;
	}
	
	void deinitialize() {
		// Not initialized.
		isInitialized = false;
		
		// Stop & deallocate threads.
		Stockfish::Threads.stop = true;
		Stockfish::Threads.set(0);		
	}
	
	bool is_uci_initialized() {
		return isUciInitialized;
	}
	
	void initialize_uci() {
		Stockfish::UCI::init(Stockfish::Options);
		
		// UCI initialized.
		isUciInitialized = true;
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
