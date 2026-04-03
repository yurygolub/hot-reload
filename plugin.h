#ifndef PLUGIN_H_
#define PLUGIN_H_

#ifdef _WIN32
#ifndef DECLSPEC
#define DECLSPEC __declspec(dllexport)
#endif // DECLSPEC
#endif // _WIN32

#ifdef _WIN32
DECLSPEC void greet(void);
#endif // _WIN32

#endif // PLUGIN_H_