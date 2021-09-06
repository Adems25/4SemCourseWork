#include "pch.h"
#include "CppUnitTest.h"
#include "../CourseWork4Sem/coursework.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace courseworkUnitTests
{
	TEST_CLASS(courseworkUnitTests)
	{
	public:

		TEST_METHOD(constructor_exception1)
		{
			string msg;
			string expected = "Could not open file F";
			try
			{
				OrGraph G("F");
			}
			catch (exception& e)
			{
				msg = e.what();
			}
			Assert::AreEqual(expected, msg);
		}

		TEST_METHOD(constructor_exception2)
		{
			ofstream test("test.txt");
			test.close();
			string msg;
			string expected = "Incorrect input";
			try
			{
				OrGraph G("test.txt");
			}
			catch (exception& e)
			{
				msg = e.what();
			}
			Assert::AreEqual(expected, msg);
		}

		TEST_METHOD(constructor_exception3)
		{
			ofstream test("test.txt");
			test << "S;A;3";
			test.close();
			string msg;
			string expected = "Graph must contain S- and T- elements";
			try
			{
				OrGraph G("test.txt");
			}
			catch (exception& e)
			{
				msg = e.what();
			}
			Assert::AreEqual(expected, msg);
		}

		TEST_METHOD(max_flow1)
		{
			ofstream test("test.txt");
			test << "S;O;3\n";
			test << "S;P;3\n";
			test << "O;Q;3\n";
			test << "O;P;2\n";
			test << "P;R;2\n";
			test << "Q;R;4\n";
			test << "Q;T;2\n";
			test << "R;T;3";
			test.close();

			int expected = 5;
			OrGraph G("test.txt");
			Assert::AreEqual(expected, G.get_max_flow());
		}

		TEST_METHOD(max_flow2)
		{
			ofstream test("test.txt");
			test << "S;O;3\n";
			test << "S;P;3\n";
			test << "O;Q;3\n";
			test << "O;P;2\n";
			test << "P;R;2\n";
			test << "Q;R;4\n";
			test << "Q;T;2\n";
			test << "R;T;3\n";

			test << "R;X;1\n";
			test << "X;P;1\n";

			test << "O;Z;1\n";
			test << "Z;V;1";

			test.close();

			int expected = 5;
			OrGraph G("test.txt");
			Assert::AreEqual(expected, G.get_max_flow());
		}

		TEST_METHOD(max_flow3)
		{
			ofstream test("test.txt");
			test << "S;O;3\n";
			test << "S;P;3\n";
			test << "O;Q;3\n";
			test << "O;P;2\n";
			test << "P;R;2\n";
			test << "Q;R;4\n";

			test << "X;T;1";

			test.close();

			int expected = 0;
			OrGraph G("test.txt");
			Assert::AreEqual(expected, G.get_max_flow());
		}

		TEST_METHOD(max_flow4)
		{
			ofstream test("test.txt");
			test << "S;A;8\n";
			test << "S;B;4\n";
			test << "S;C;2\n";

			test << "A;B;2\n";
			test << "B;C;1\n";

			test << "A;D;9\n";
			test << "B;E;3\n";
			test << "C;F;1\n";

			test << "E;F;2\n";

			test << "D;G;8\n";
			test << "E;H;2\n";
			test << "F;I;3\n";

			test << "G;H;5\n";
			test << "H;I;4\n";

			test << "G;T;4\n";
			test << "H;T;3\n";
			test << "I;T;6";

			test.close();

			int expected = 12;
			OrGraph G("test.txt");
			Assert::AreEqual(expected, G.get_max_flow());
		}

		TEST_METHOD(max_flow5)
		{
			ofstream test("test.txt");
			test << "S;A;8\n";
			test << "S;B;4\n";
			test << "S;C;2\n";

			test << "A;B;2\n";
			test << "B;C;1\n";

			test << "A;D;9\n";
			test << "C;F;2\n";

			test << "D;G;8\n";
			test << "F;I;1\n";

			test << "G;H;5\n";
			test << "H;I;1\n";

			test << "G;T;4\n";
			test << "H;T;3\n";
			test << "I;T;6";

			test.close();

			int expected = 9;
			OrGraph G("test.txt");
			Assert::AreEqual(expected, G.get_max_flow());
		}

		TEST_METHOD(max_flow6)
		{
			ofstream test("test.txt");
			test << "S;D;3\n";
			test << "S;C;8\n";
			test << "S;T;2\n";
			test << "D;T;4\n";
			test << "C;T;2";

			test.close();

			int expected = 7;
			OrGraph G("test.txt");
			Assert::AreEqual(expected, G.get_max_flow());
		}
	};
}

