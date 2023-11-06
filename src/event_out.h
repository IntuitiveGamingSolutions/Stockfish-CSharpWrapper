#ifndef EVENT_OUT_H
#define EVENT_OUT_H

#include "event_output_stream.h"

namespace StockfishWrapper {
	namespace IO {
		extern EventOutputStream event_out;
        void set_event_out_callback(EventOutputStream::OutputReceivedCallback callback);
	}
}
#endif
