#include <string>
#include <httplib.h>

#include "config.hpp"

namespace notifier
{
	httplib::Client* clientResponse = nullptr;
	httplib::Client* clientRequest = nullptr;

	void init()
	{
		auto& c = config::get();

		if (!c.enable_notifier) return;

		clientResponse = new httplib::Client(c.notifier_send_response_host.data());
		clientResponse->set_connection_timeout(0, c.notifier_connection_timeout_msec * 1000);

		clientRequest = new httplib::Client(c.notifier_send_request_host.data());
		clientRequest->set_connection_timeout(0, c.notifier_connection_timeout_msec * 1000);
	}

	void notify_response(const std::string& data)
	{
		if (clientResponse == nullptr) return;

		if (auto res = clientResponse->Post("/response", data, "application/x-msgpack"))
		{
			if (res->status != 200)
			{
				std::cout << "Unexpected response from listener: " << res->status << "\n";
			}
		}
		else
		{
			if (config::get().notifier_print_error)
			{
				std::cout << "Failed to notify listener: " << res.error() << "\n";
			}
		}
	}

	void notify_request(const std::string& data)
	{
		if (clientRequest == nullptr) return;

		if (auto res = clientRequest->Post("/request", data, "application/x-msgpack"))
		{
			if (res->status != 200)
			{
				std::cout << "Unexpected request from listener: " << res->status << "\n";
			}
		}
		else
		{
			if (config::get().notifier_print_error)
			{
				std::cout << "Failed to notify listener: " << res.error() << "\n";
			}
		}
	}
}
