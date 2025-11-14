#ifndef PLUGIN_H_
#define PLUGIN_H_

#ifndef DECLSPEC
  #define DECLSPEC __declspec(dllexport)
#endif

DECLSPEC void greet(void);

#endif // PLUGIN_H_