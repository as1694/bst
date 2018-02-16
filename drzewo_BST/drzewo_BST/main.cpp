#include <iostream>
#include <gtest\gtest.h>
#include <gmock\gmock.h>


using namespace std;

class drzewo
{
public:
	struct wezel
	{
		int key;
		wezel* pLeft=nullptr;
		wezel* pRight=nullptr;
	};

	wezel* root = nullptr;

	void dodajWezel()
	{
		int klucz = 0;
		cout << "podaj wartosc wezla jaki chcesz dodac" << endl;
		cin >> klucz;


		if (root == nullptr)
		{
			root = new wezel;
			root->key = klucz;
			root->pLeft = nullptr;
			root->pRight = nullptr;
		}

		else
		{
			wezel* p = root;
			wezel* parent = nullptr;
			bool LR = 0; // 0 - left, 1 - right

			while (p != nullptr)
			{
				if (p->key == klucz)
				{
					cout << "w drzewie istnieje juz taki wezel" << endl;
					return;
				}
				
				else
				{
					parent = p;

					if (p->key > klucz)
					{
						p = p->pLeft;
						LR = 0;
					}
					else
					{
						p = p->pRight;
						LR = 1;
					}
				}
			}

			if (LR == 0)
			{
				parent->pLeft = new wezel;
				parent->pLeft->key = klucz;
			}
			else

			{
				parent->pRight = new wezel;
				parent->pRight->key = klucz;
			}
		}
	}

	void usunWezel()
	{
		int klucz = 0;
		cout << "podaj nr wezla, ktory chcesz usunac" << endl;
		cin >> klucz;

		wezel* p = root;
		wezel* parent = nullptr;

		bool LR = 0; //0 -lewo 1- prawo

		while (p != nullptr && klucz != p->key)
		{
			parent = p;
			if (p->key > klucz)
			{
				p = p->pLeft;
				LR = 0;
			}
			else
			{
				p = p->pRight;
				LR = 1;
			}
		}
		if (p == nullptr)
			cout << "brak wezla o podanym numerze" << endl;
		else
		{
			//usuwany wezel jest lisciem
			if (p->pLeft == nullptr && p->pRight == nullptr)
			{
				//wezel jest lisciem i korzeniem
				if (p == root)
				{
					root = nullptr;
					cout << "usunales drzewo wraz z korzeniem" << endl;
					return;
				}

				//tylko lisciem
				else
				{
					if (parent->pLeft == p)
						parent->pLeft = nullptr;
					else
						parent->pRight = nullptr;

					cout << "usunieto wezel " << klucz << endl;
					return;
				}
			}

			//usuwamy wezel, ktory nie jest lisciem i korzeniem
			if (p != root)
			{
				//usuwany wezel ma tylko lewe poddrzewo
				if (p->pRight == nullptr)
				{
					if (parent->pRight == p)
						parent->pRight = p->pLeft;
					else
						parent->pLeft = p->pLeft;
					return;
				}

				//usuwany wezel ma tylko prawe poddrzewo
				if (p->pLeft == nullptr)
				{
					if (parent->pRight == p)
						parent->pRight = p->pRight;
					else
						parent->pLeft = p->pRight;
					return;
				}
			}

			//usuwamy korzen, ktory nie jest lisciem i ma jedno poddrzewo
			if (p == root && (root->pLeft == nullptr || root->pRight == nullptr)) 
			{
				if (root->pLeft == nullptr)
					root = p->pRight;
				else
					root = p->pLeft;
				return;
			}

			//usuwany wezel ma dwa poddrzewa
			//i jest korzeniem
			if (p == root)
			{
				wezel* parentP = poprzednikParentPointer(root);
				wezel* poprzednik = poprzednikPointer(root);

				if (parentP != root)
				{
					parentP->pRight = poprzednik->pLeft;
				}
				poprzednik->pLeft = root->pLeft;
				poprzednik->pRight = root->pRight;
				root = poprzednik;

				return;
			}

			//nie jest korzeniem
			else
			{
				wezel* parentP = poprzednikParentPointer(p);
				wezel* poprzednik = poprzednikPointer(p);

				if (parentP->pRight != nullptr)
				{
					parentP->pRight = poprzednik->pLeft;
					poprzednik->pLeft = p->pLeft;
					poprzednik->pRight = p->pRight;
				}
				else
				{
					poprzednik->pRight = p->pRight;
				}

				if (LR == 0)
					parent->pLeft = poprzednik;
				else
					parent->pRight = poprzednik;

				return;
			}
		}

	}


	void wyswietl()
	{
		if (root == nullptr)
			cout << "drzewo jest puste" << endl;

		else
		{
			int tab[5][35];

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 35; j++)
					tab[i][j] = 0;
				
			}

			wezel* p = root;
			wezel* p1 = nullptr;
			wezel* p2 = nullptr;
			wezel* p3 = nullptr;
			wezel* p4 = nullptr;
			wezel* p5 = nullptr;

			tab[0][15] = p->key;

 			if (p->pLeft != nullptr)
			{
				tab[1][6] = lewy(p);
				
				p = p->pLeft;
				p1 = p;
				

				if (p->pLeft != nullptr)
				{
					tab[2][3] = lewy(p);
					p = p->pLeft;
					p2 = p;

					if (p->pLeft != nullptr)
					{
						tab[3][1] = lewy(p);
						p = p->pLeft;
						p4 = p;

						if (p->pLeft != nullptr)
						{
							tab[4][0] = lewy(p);
							//p = p->pLeft;
							//p2 = p;
						}

						if (p4->pRight != nullptr)
						{
							tab[4][2] = prawy(p4);
							//p1 = p->pRight;
							//p3 = p1;
						}
					}

					if (p2->pRight != nullptr)
					{
						tab[3][5] = prawy(p2);
						p2 = p2->pRight;
						p5 = p2;

						if (p2->pLeft != nullptr)
						{
							tab[4][4] = lewy(p2);
							//p = p->pLeft;
							//p2 = p;
						}

						if (p5->pRight != nullptr)
						{
							tab[4][6] = prawy(p5);
							//p1 = p->pRight;
							//p3 = p1;
						}
					}
				}

				if (p1->pRight != nullptr)
				{
					tab[2][11] = prawy(p1);
					p1 = p1->pRight;
					p3 = p1;

					if (p1->pLeft != nullptr)
					{
						tab[3][8] = lewy(p1);
						p1 = p1->pLeft;
						p2 = p1;
						if (p1->pLeft != nullptr)
						{
							tab[4][7] = lewy(p1);
							//p = p->pLeft;
							//p2 = p;
						}

						if (p2->pRight != nullptr)
						{
							tab[4][9] = prawy(p2);
							//p1 = p->pRight;
							//p3 = p1;
						}
					}

					if (p3->pRight != nullptr)
					{
						tab[3][13] = prawy(p3);
						p3 = p3->pRight;
						p4 = p3;
						if (p3->pLeft != nullptr)
						{
							tab[4][13] = lewy(p3);
							//p = p->pLeft;
							//p2 = p;
						}

						if (p4->pRight != nullptr)
						{
							tab[4][15] = prawy(p4);
							//p1 = p->pRight;
							//p3 = p1;
						}
					}
				}

			}


			p = root;
			if (p->pRight != nullptr)
			{
				tab[1][24] = prawy(p);
				p = p->pRight;
				p1 = p;

				if (p->pLeft != nullptr)
				{
					tab[2][21] = lewy(p);
					p = p->pLeft;
					p2 = p;

					if (p->pLeft != nullptr)
					{
						tab[3][18] = lewy(p);
						p = p->pLeft;
						p4 = p;

						if (p->pLeft != nullptr)
						{
							tab[4][17] = lewy(p);
							//p = p->pLeft;
							//p2 = p;
						}

						if (p4->pRight != nullptr)
						{
							tab[4][19] = prawy(p4);
							//p1 = p->pRight;
							//p3 = p1;
						}
					}

					if (p2->pRight != nullptr)
					{
						tab[3][24] = prawy(p2);
						p2 = p2->pRight;
						p5 = p2;

						if (p2->pLeft != nullptr)
						{
							tab[4][23] = lewy(p2);
							//p = p->pLeft;
							//p2 = p;
						}

						if (p5->pRight != nullptr)
						{
							tab[4][25] = prawy(p5);
							//p1 = p->pRight;
							//p3 = p1;
						}
					}
				}

				if (p1->pRight != nullptr)
				{
					tab[2][29] = prawy(p1);
					p1 = p1->pRight;
					p3 = p1;

					if (p1->pLeft != nullptr)
					{
						tab[3][27] = lewy(p1);
						p1 = p1->pLeft;
						p2 = p1;
						if (p1->pLeft != nullptr)
						{
							tab[4][26] = lewy(p1);
							//p = p->pLeft;
							//p2 = p;
						}

						if (p2->pRight != nullptr)
						{
							tab[4][28] = prawy(p2);
							//p1 = p->pRight;
							//p3 = p1;
						}
					}

					if (p3->pRight != nullptr)
					{
						tab[3][32] = prawy(p3);
						p3 = p3->pRight;
						p4 = p3;
						if (p3->pLeft != nullptr)
						{
							tab[4][31] = lewy(p3);
							//p = p->pLeft;
							//p2 = p;
						}

						if (p4->pRight != nullptr)
						{
							tab[4][33] = prawy(p4);
							//p1 = p->pRight;
							//p3 = p1;
						}
					}
				}
			}




			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 35; j++)
				{
					if (tab[i][j] != 0)
						cout << tab[i][j] << " ";
					else
						cout << "   ";
				}
				cout << endl;
				cout << endl;
			}
		}
	}

//private:
	int lewy(wezel* parent)
	{
		return parent->pLeft->key;
	}

	int prawy(wezel* parent)
	{
		return parent->pRight->key;
	}

	int poprzednik(wezel* del)
	{
		wezel* p = del;
		//wezel* parent = nullptr;

		if (p->pLeft == nullptr)
		{
			cout << "brak poprzednika" << endl;
			return -1;
		}
		else
		{
			p = p->pLeft;
			while (p->pRight != nullptr)
			{
				//parent = p;
				p = p->pRight;
			}
			cout << "poprzednik korzenia "<<p->key << endl;
			system("pause");
			return p->key;
		}
	}

	wezel* poprzednikPointer(wezel* del)
	{
		wezel* p = del;
		wezel* parent = nullptr;

		if (p->pLeft == nullptr)
		{
			cout << "brak poprzednika" << endl;
			return nullptr;
		}
		else
		{
			
			p = p->pLeft;
			parent = p;
			
			while (p->pRight != nullptr)
			{
				parent = p;
				p = p->pRight;
			}
			//cout << "poprzednik korzenia " << p->key << endl;
			//system("pause");
			if (parent->pRight != 0)
				return parent->pRight;
			else
				return parent;
		}
	}

	wezel* poprzednikParentPointer(wezel* del)
	{
		wezel* p = del;
		wezel* parent = nullptr;

		if (p->pLeft == nullptr)
		{
			cout << "brak poprzednika" << endl;
			return nullptr;
		}
		else
		{
			p = p->pLeft;
			parent = p;
			while (p->pRight != nullptr)
			{
				parent = p;
				p = p->pRight;
			}
		
			if (parent != nullptr)
				return parent;
			else
				return nullptr;
		}


	}
};



int main2()
{

	int wybor = 0;
	drzewo test;

	do {

		cout << "1 - dodaj wezel" << endl;
		cout << "2 - wyswietl" << endl;
		cout << "3 - usun wezel" << endl;
		cout << "4 - poprzednik korzenia" << endl;
		cout << "5 - " << endl;
		cout << "6 - koniec" << endl;

		cin >> wybor;
		//system("cls");
		switch (wybor)
		{
		case 1: test.dodajWezel(); break;
		case 2: test.wyswietl(); break;
		case 3: test.usunWezel(); break;
		case 4: test.poprzednik(test.root); break;
		case 5: ; break;
		case 6: return 0; break;
		default: cout << "blad" << endl; break;
		}
		system("cls");
		test.wyswietl();

		cout << endl;

	} while (wybor != 6);
	return 0;
}


struct TestStruct : public ::testing::Test
{

	virtual void SetUp() override
	{

	}

	drzewo drzewo;

	// Inherited via Test
	virtual void TestBody() override
	{
	}
};

TEST_F(TestStruct, dummytest)
{
	//drzewo.dodajWezel();
	EXPECT_TRUE(2+3==5);
}

TEST(dddd)
{
	EXPECT_TRUE(true);
}

int main(int argc, char**argv)
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);

	
	auto r = RUN_ALL_TESTS();
	system("pause");
}