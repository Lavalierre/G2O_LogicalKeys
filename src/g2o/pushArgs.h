#ifndef _PUSH_ARGS_H
#define _PUSH_ARGS_H

namespace SqModule
{
	void pushArg() {}

	template <class T>
	void pushArg(T t)
	{
		Sqrat::PushVar(vm, t);
	}

	template <class T, class ...vargv >
	void pushArg(T t, vargv... args)
	{
		Sqrat::PushVar(vm, t);
		pushArgs(args...);
	}

	template <class ...vargv >
	void pushArgs(vargv... args)
	{
		pushArg(args...);
	}
}

#endif