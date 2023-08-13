//
// Basic instrumentation profiler by Cherno

// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// instrumentor::Get().BeginSession("Session Name");        // Begin session 
// {
//     InstrumentationTimer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// instrumentor::Get().EndSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile name.
//
#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

struct profile_result
{
    std::string name;
    long long start, end;
    size_t thread_id;
};

struct instrumentation_session
{
    std::string name;
};

class instrumentor
{
public:
    instrumentor()
        : m_current_session_(nullptr), m_profile_count_(0)
    {
    }

    void begin_session(const std::string& name, const std::string& filepath = "results.json")
    {
        m_output_stream_.open(filepath);
        write_header();
        m_current_session_ = new instrumentation_session{ name };
    }

    void end_session()
    {
        write_footer();
        m_output_stream_.close();
        delete m_current_session_;
        m_current_session_ = nullptr;
        m_profile_count_ = 0;
    }

    void write_profile(const profile_result& result)
    {
        if (m_profile_count_++ > 0)
            m_output_stream_ << ",";

        std::string name = result.name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_output_stream_ << "{";
        m_output_stream_ << R"("cat":"function",)";
        m_output_stream_ << "\"dur\":" << result.end - result.start << ',';
        m_output_stream_ << R"("name":")" << name << "\",";
        m_output_stream_ << R"("ph":"X",)";
        m_output_stream_ << "\"pid\":0,";
        m_output_stream_ << "\"tid\":" << result.thread_id << ",";
        m_output_stream_ << "\"ts\":" << result.start;
        m_output_stream_ << "}";

        m_output_stream_.flush();
    }

    void write_header()
    {
        m_output_stream_ << R"({"otherData": {},"traceEvents":[)";
        m_output_stream_.flush();
    }

    void write_footer()
    {
        m_output_stream_ << "]}";
        m_output_stream_.flush();
    }

    static instrumentor& get()
    {
        static instrumentor instance;
        return instance;
    }

private:
    instrumentation_session* m_current_session_;
    std::ofstream m_output_stream_;
    int m_profile_count_;
};

class instrumentation_timer
{
public:
	explicit instrumentation_timer(const char* name)
        : m_name_(name), m_stopped_(false)
    {
        m_start_time_point_ = std::chrono::high_resolution_clock::now();
    }

    ~instrumentation_timer()
    {
        if (!m_stopped_)
            stop();
    }

    void stop()
    {
	    const auto end_time_point = std::chrono::high_resolution_clock::now();

	    const long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_time_point_).time_since_epoch().count();
	    const long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();

	    const auto thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
        instrumentor::get().write_profile({ m_name_, start, end, thread_id });

        m_stopped_ = true;
    }
private:
    const char* m_name_;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time_point_;
    bool m_stopped_;
};