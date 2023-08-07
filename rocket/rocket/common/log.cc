#include <sys/time.h>
#include <sstream>
#include <stdio.h>
#include "rocket/common/util.h"
#include "rocket/common/log.h"








namespace rocket {
static Logger* g_logger = NULL;

Logger* Logger::GetGlobalLogger() {
  return g_logger;
}
    
std::string LogLevelToString(LogLevel level) {
  switch (level) {
  case Debug:
    return "DEBUG";

  case Info:
    return "INFO";

  case Error:
    return "ERROR";
  default:
    return "UNKNOWN";
  }
}

std::string LogEvent::toString() {
  struct timeval now_time; //timeval is time struct of linux,which consists of tv_sec and usec

  gettimeofday(&now_time, nullptr);  //man gettimeofday to know

  struct tm now_time_t; //whicn consists of tm_year,mon,mday,hour,min,sec
  localtime_r(&(now_time.tv_sec), &now_time_t);

  char buf[128];
  strftime(&buf[0], 128, "%y-%m-%d %H:%M:%S", &now_time_t); //trans struct to char buf
  std::string time_str(buf);
  int ms = now_time.tv_usec / 1000;
  time_str = time_str + "." + std::to_string(ms);


  m_pid = getPid();
  m_thread_id = getThreadId();

  std::stringstream ss;

  ss << "[" << LogLevelToString(m_level) << "]\t"
    << "[" << time_str << "]\t"
    << "[" << m_pid << ":" << m_thread_id << "]\t";

  // 获取当前线程处理的请求的 msgid

  //std::string msgid = RunTime::GetRunTime()->m_msgid;
  //std::string method_name = RunTime::GetRunTime()->m_method_name;
  // if (!msgid.empty()) {
  //   ss << "[" << msgid << "]\t";
  // }

  // if (!method_name.empty()) {
  //   ss << "[" << method_name << "]\t";
  // }
  return ss.str();
}

void Logger::pushLog(const std::string& msg) {
  if (m_type == 0) {
    printf((msg + "\n").c_str());
    return;
  }
  //ScopeMutex<Mutex> lock(m_mutex);
  m_buffer.push_back(msg);
  //lock.unlock();
}

void Logger::log(){

}







}