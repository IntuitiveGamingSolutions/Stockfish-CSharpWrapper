#include "event_out.h"

namespace StockfishWrapper {
	namespace IO {
		EventOutputStream event_out;
        
        void set_event_out_callback(EventOutputStream::OutputReceivedCallback callback) {
            event_out.set_output_callback(callback);
        }
	}
}
