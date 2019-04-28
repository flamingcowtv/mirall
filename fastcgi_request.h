#pragma once

#include <unordered_map>

#include "buffer.h"

class FastCGIConn;

class FastCGIRequest {
  public:
    FastCGIRequest(uint16_t request_id, FastCGIConn *conn);

	void AddParam(const std::string_view& key, const std::string_view& value);
	void AddIn(const std::string_view& in);

	const std::string& GetParam(const std::string& key);

	void WriteHeader(const std::string_view& name, const std::string_view& value);
	void WriteBody(const std::string_view& body);
	void Flush();
	void End();

  private:
	const uint16_t request_id_;
	FastCGIConn *conn_;

	std::unordered_map<std::string, std::string> params_;
	std::string in_;

	Buffer out_buf_;
	bool body_sent_ = false;
};
