// ManagedDll.h
#pragma once
#include <string>  
#include <iostream>  

using namespace System;
using namespace System::Reflection;
using namespace std;

string MarshalString(String ^ s) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	string os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return os;
}

namespace ManagedDll {	

	public ref class DoWork
	{
		
	public:int ShowCSharpMessageBox()
	{
		return ManagedCSharp::ManagedClass::ShowValue();
	}
	public:int GetValue()
	{
		return ManagedCSharp::ManagedClass::GetValue();
	}
	public:void ChangeValue(int value)
	{
		ManagedCSharp::ManagedClass::ChangeValue(value);
	}
	public:void Connect(int port)
	{
		ManagedCSharp::ManagedClass::Connect(port);
	}
	public:void Disconnect()
	{
		ManagedCSharp::ManagedClass::Disconnect();
	}
	public:bool IsConnected()
	{
		return ManagedCSharp::ManagedClass::IsConnected();
	}
	public:void SendMessage(char *title, char * value)
	{
		ManagedCSharp::ManagedClass::SendMessage(gcnew String(title), gcnew String(value));
	}
	public:void SendMessage(char* title, float value)
	{
		ManagedCSharp::ManagedClass::SendMessage(gcnew String(title), value);
	}
	public:void SendMessage(char* title, bool value)
	{
		ManagedCSharp::ManagedClass::SendMessage(gcnew String(title), value);
	}
	public:int GetAvilableMessages()
	{
		return ManagedCSharp::ManagedClass::GetAvilableMessages();
	}
	public:bool AvilableMessage()
	{
		return ManagedCSharp::ManagedClass::AvilableMessage();
	}
	public:bool UpdateMessageReciver()
	{
		return ManagedCSharp::ManagedClass::UpdateMessageReciving();
	}
	public:string ReadMessageTitle()
	{
		return MarshalString(ManagedCSharp::ManagedClass::ReadMessageTitle());
	}
	public:string ReadMessageText()
	{
		return MarshalString(ManagedCSharp::ManagedClass::ReadMessageText());
	}
	public:float ReadMessageNumber()
	{
		return ManagedCSharp::ManagedClass::ReadMessageNumber();
	}
	public:bool ReadMessageLogic()
	{
		return ManagedCSharp::ManagedClass::ReadMessageLogic();
	}
	};
}

__declspec(dllexport)string ReadMessageTitle()
{
	ManagedDll::DoWork work;
	return work.ReadMessageTitle();
}
__declspec(dllexport)string ReadMessageText()
{
	ManagedDll::DoWork work;
	return work.ReadMessageText();
}
__declspec(dllexport)float ReadMessageNumber()
{
	ManagedDll::DoWork work;
	return work.ReadMessageNumber();
}
__declspec(dllexport)bool UpdateMessageReciver()
{
	ManagedDll::DoWork work;
	return work.UpdateMessageReciver();
}

__declspec(dllexport)bool ReadMessageLogic()
{
	ManagedDll::DoWork work;
	return work.ReadMessageLogic();
}	    	
__declspec(dllexport) bool IsConnected()
{
	ManagedDll::DoWork work;
	return work.IsConnected();
}
__declspec(dllexport) void Disconnect()
{
	ManagedDll::DoWork work;
	work.Disconnect();
}
__declspec(dllexport) void Connect(int port)
{
	ManagedDll::DoWork work;
	work.Connect(port);
}
__declspec(dllexport) void SendMessageN(char* title, float value)
{
	ManagedDll::DoWork work;
	work.SendMessage( title, value);
}
__declspec(dllexport) void SendMessageT(char* title, char* value)
{
	ManagedDll::DoWork work;
	work.SendMessage(title, value);
}
__declspec(dllexport) void SendMessageL(char* title, bool value)
{
	ManagedDll::DoWork work;
	work.SendMessage(title,value);
}
__declspec(dllexport) int GetAvilableMessages()
{
	ManagedDll::DoWork work;
	return work.GetAvilableMessages();
}
__declspec(dllexport) bool AvilableMessage()
{
	ManagedDll::DoWork work;
	return work.AvilableMessage();
}

__declspec(dllexport) int GetValue()
{
	ManagedDll::DoWork work;	
	return work.GetValue();	
}
__declspec(dllexport) void ChangeValue(int value)
{
	ManagedDll::DoWork work;
	work.ChangeValue(value);
}
__declspec(dllexport) int ShowMessageBox()
{
	ManagedDll::DoWork work;
	return work.ShowCSharpMessageBox();
}







