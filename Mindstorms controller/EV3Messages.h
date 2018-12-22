#pragma once
#include <vector>
using namespace std;

string ReadMessageTitle();
string ReadMessageText();
float ReadMessageNumber();
bool ReadMessageLogic();
 int GetAvilableMessages();
 bool AvilableMessage();
bool UpdateMessageReciver();

class EV3Messages
{
public:
	struct NumberMessage
	{
		string title;
		float number;
	};
	struct LogicMessage
	{
		string title;
		bool logic;
	};
	struct TextMessage
	{
		string title;
		string text;
	};
	class Message
	{
	public:
		Message(string title, string text, float number, bool logic)
			:
			title(title),
			text(text),
			number(number),
			logic(logic)
		{}
		NumberMessage ToNumberMessage()
		{
			return NumberMessage{ title,number };
		}
		TextMessage ToTextMessage()
		{
			return TextMessage{ title,text };
		}
		LogicMessage ToLogicMessage()
		{
			return LogicMessage{ title, logic };
		}
		string title;
		string text;
		float number;
		bool logic;
	};

	static string MessageToString(Message& msg)
	{
		string str;
		str += "Message title" + msg.title + " Text: " + msg.text + " Number: " + to_string(msg.number) + " Logic: " + to_string(msg.logic);
		return str;
	}

	void UpdateNewMessages()
	{
		while (UpdateMessageReciver())
		{
			string title = ReadMessageTitle();
			string text = ReadMessageText();
			float number = ReadMessageNumber();
			bool logic = ReadMessageLogic();
			messages.emplace_back(Message{ title,text,number,logic });
		}
	}
	Message GetFirstMessage(bool deleteM = true)
	{
		Message msg = messages[0];
		if (deleteM)
			messages.erase(messages.begin());
		return msg;
	}
	vector<Message> GetTitleMessages(string& title, bool deleteM = true)
	{
		vector<Message> RetMsgs;
		for (int i = 0; i < messages.size(); i++)
		{
			if (messages[i].title == title)
			{
				RetMsgs.emplace_back(messages[i]);
				if (deleteM)
				{
					messages.erase(messages.begin() + i);
				}
			}
		}
		return RetMsgs;
	}
	vector<EV3Messages::NumberMessage> GetTitleMessagesNumber(string& title, bool deleteM = true)
	{
		vector<EV3Messages::NumberMessage> RetMsgs;
		for (int i = 0; i < messages.size(); i++)
		{
			if (messages[i].title == title)
			{
				RetMsgs.emplace_back(messages[i].ToNumberMessage());
				if (deleteM)
				{
					messages.erase(messages.begin() + i);
				}
			}
		}
		return RetMsgs;
	}
	vector<EV3Messages::TextMessage> GetTitleMessagesText(string& title, bool deleteM = true)
	{
		vector<EV3Messages::TextMessage> RetMsgs;
		for (int i = 0; i < messages.size(); i++)
		{
			if (messages[i].title == title)
			{
				RetMsgs.emplace_back(messages[i].ToTextMessage());
				if (deleteM)
				{
					messages.erase(messages.begin() + i);
				}
			}
		}
		return RetMsgs;
	}
	vector<Message>& GetMessages()
	{
		return messages;
	}
private:
	vector<Message> messages;
};