#pragma once
#include <string>

namespace config
{
	struct config_struct
	{
		bool save_request;
		bool save_response;

		bool enable_ansi_colors;

		bool enable_notifier;
		std::string notifier_send_response_host;
		std::string notifier_send_request_host;
		int notifier_connection_timeout_msec;
		bool notifier_print_error;

		bool aoharu_team_sort_with_speed;
	};

	void load();

	config_struct const& get();
}
