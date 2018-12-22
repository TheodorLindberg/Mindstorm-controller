using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using EV3MessengerLib;
namespace ManagedCSharp
{
    public static class ManagedClass
    {
        public static List<EV3Message> messages = new List<EV3Message>();
        public static int Value;
        private static EV3Messenger messenger = new EV3Messenger();
        public static SerialPort port;

        public static int ShowValue()
        {
            DialogResult result = MessageBox.Show("C# Message Box", "C# Message Box", MessageBoxButtons.OKCancel);
            if (result == DialogResult.OK)
                return 1;
            else
                return 2;
        }
        public static int GetValue()
        {
            return Value;
        }
        public static void ChangeValue(int newvalue)
        {
            Value = newvalue;
        }
        public static bool UpdateMessageReciving()
        {
            if (messenger.IsConnected)
            {
                EV3Message message = messenger.ReadMessage();
                if (message != null)
                {
                    messages.Add(message);
                    return true;
                }
            }
            return false;
        }
        //EV3 messanger function lib
        public static void Connect(int port)
        {

            messenger.Connect("COM" + port.ToString());
        }
        public static void Disconnect()
        {
            messenger.Disconnect();
        }
        public static bool IsConnected()
        {
            return messenger.IsConnected;
        }
        public static void SendMessage(string title, string value)
        {
            messenger.SendMessage(title, value);
        }
        public static void SendMessage(string title, float value)
        {
            messenger.SendMessage(title.ToString(), value);
        }
        public static void SendMessage(string title, bool value)
        {
            messenger.SendMessage(title.ToString(), value);
        }
        public static int GetAvilableMessages()
        {
            return messages.Count;
        }
        public static bool AvilableMessage()
        {
            return messages.Count > 0;
        }
        public static string ReadMessageTitle()
        {
            return messages[0].MailboxTitle;
        }
        public static string ReadMessageText()
        {
            return messages[0].ValueAsText;
        }
        public static float ReadMessageNumber()
        {
            return messages[0].ValueAsNumber;
        }
        public static bool ReadMessageLogic()
        {
            bool message = messages[0].ValueAsLogic;
            messages.RemoveAt(0);
            return message;
        }
    }
}
