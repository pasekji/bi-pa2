#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST__ */

/**
  # Person class definition
    used for personal data representation
**/
class CPerson
{
public:

	CPerson(const string& name, const string& addr, const string& account) : sumIncome(0), sumExpense(0), account(account), name(name), addr(addr)
	{}

	int sumIncome;
	int sumExpense;
	string account;
	string name;
	string addr;

};

class CTaxRegister;

/**
  # Iterator class definition
    used for iterating over CTaxRegister
**/
class CIterator
{
private:

	const CTaxRegister* reg;
	unsigned index;

public:

	CIterator	(const CTaxRegister* reg) : reg(reg), index(0)
	{}
	bool                     AtEnd(void) const;
	void                     Next(void);
	string                   Name(void) const;
	string                   Addr(void) const;
	string                   Account(void) const;
};

/**
  # Tax register class definition
    used for representation and manipulation over CPerson objects
**/
class CTaxRegister
{
	public:

	// vector of CPerson* sorted by name
	vector<CPerson*> peopleByName;

	bool	Birth	(const string& name, const string& addr, const string& account);
	bool	Death	(const string& name, const string& addr);
	bool	Income	(const string& account, int amount);
	bool	Income	(const string& name, const string& addr, int amount);
	bool Expense	(const string& account, int amount);
	bool Expense	(const string& name, const string& addr, int amount);
	bool	Audit	(const string& name, const string& addr, string& account, int& sumIncome, int& sumExpense) const;
	CIterator	ListByName	(void) const;
	~CTaxRegister();

	private:

	// vector of CPerson* sorted by account number
	vector<CPerson*> peopleByAccount;

	CPerson*	FindByName	(const string& name, const string& addr) const;
	CPerson*	FindByAccount	(const string& account) const;
	bool	Income	(CPerson* person, int amount);
	bool	Expense	(CPerson* person, int amount);
};

/*
	bool compareByName(CPerson* p1, CPerson* p2);
	compares two CPerson objects based on name and address
	returns: true if p1->name is less than p2->name or if names are equal and p1->addr is less than p2->addr,
					 false otherwise
*/
bool	compareByName	(CPerson* p1, CPerson* p2)
{
	return
		(p1->name < p2->name)
	||
		(p1->name == p2->name && p1->addr < p2->addr);
}

/*
	bool compareByAccount(CPerson* p1, CPerson* p2);
	compares two CPerson objects based on account number
	returns: true if p1->account is less than p2->account,
					 false otherwise
*/
bool	compareByAccount	(CPerson* p1, CPerson* p2)
{
	return p1->account < p2->account;
}

/*
	bool CTaxRegister::Birth(const string& name, const string& addr, const string& account);
	checks if same instance of CPerson is not already availiable in register, if not creates new instance and inserts it into sorted vectors
	returns: true if the same CPerson does not already exist,
					 false otherwise
*/
bool CTaxRegister::Birth	(const string& name, const string& addr, const string& account)
{
	if (FindByName(name, addr)) return false;
	if (FindByAccount(account)) return false;

	CPerson* person = new CPerson(name, addr, account);

	peopleByName.insert(lower_bound(peopleByName.begin(), peopleByName.end(), person, compareByName), person);
	peopleByAccount.insert(lower_bound(peopleByAccount.begin(), peopleByAccount.end(), person, compareByAccount), person);

	return true;
}

/*
	bool CTaxRegister::Death(const string& name, const string& addr);
	checks if the wanted instance of CPerson is already availiable in register to than erase it from and delete it
	returns: true if wanted instance of CPerson already exists in register,
					 false otherwise
*/
bool	CTaxRegister::Death	(const string& name, const string& addr)
{
	CPerson* person = FindByName(name, addr);

	if (!person) return false;

	peopleByName.erase(lower_bound(peopleByName.begin(), peopleByName.end(), person, compareByName));
	peopleByAccount.erase(lower_bound(peopleByAccount.begin(), peopleByAccount.end(), person, compareByAccount));

	delete person;
	return true;
}

/*
	bool CTaxRegister::Income(const string& account, int amount);
	adds the amount of income to CPerson instace based on account number
	returns: true if the wanted account belongs to some CPerson instace in register and the amount was successfully added to sumIncome of that CPerson instace,
					 false otherwise
*/
bool	CTaxRegister::Income	(const string& account, int amount)
{
	return Income(FindByAccount(account), amount);
}

/*
	bool CTaxRegister::Income(const string& name, const string& addr, int amount);
	adds the amount of income to CPerson instace based on name and address
	returns: true if the wanted account belongs to some CPerson instace in register and the amount was successfully added to sumIncome of that CPerson instace,
					 false otherwise
*/
bool	CTaxRegister::Income	(const string& name, const string& addr, int amount)
{
	return Income(FindByName(name, addr), amount);
}

/*
	bool CTaxRegister::Expense(const string& account, int amount);
	adds the amount of expense to CPerson instance based on account number
	returns: true if the wanted account belongs to some CPerson instace in register and the amount was successfully added to sumExpense of that CPerson instace,
					 false otherwise
*/
bool	CTaxRegister::Expense	(const string& account, int amount)
{
	return Expense(FindByAccount(account), amount);
}

/*
	bool CTaxRegister::Expense(const string& name, const string& addr, int amount);
	adds the amount of expense to CPerson instance based on name and address
	returns: true if the wanted account belongs to some CPerson instace in register and the amount was successfully added to sumExpense of that CPerson instace,
					 false otherwise
*/
bool	CTaxRegister::Expense	(const string& name, const string& addr, int amount)
{
	return Expense(FindByName(name, addr), amount);
}

/*
	bool CTaxRegister::Audit(const string& name, const string& addr, string& account, int& sumIncome, int& sumExpense) const;
	provides the account number, sum of income and sum of outcome for the provided name and address in register
	returns: true if CPerson instace was found by the provided name and addr,
					 false otherwise
*/
bool	CTaxRegister::Audit	(const string& name, const string& addr, string& account, int& sumIncome, int& sumExpense) const
{
	CPerson* person = FindByName(name, addr);
	if (!person) return false;

	account = person->account;
	sumIncome = person->sumIncome;
	sumExpense = person->sumExpense;

	return true;
}

/*
	CPerson*	CTaxRegister::FindByName	(const string& name, const string& addr) const
	finds CPerson instance in register by provided name and address
	returns: CPerson* if instance was found,
					 nullptr otherwise
*/
CPerson*	CTaxRegister::FindByName	(const string& name, const string& addr) const
{
	CPerson tmp(name, addr, "");
	auto it = lower_bound(peopleByName.begin(), peopleByName.end(), &tmp, compareByName);

	if (it == peopleByName.end()) return nullptr;
	CPerson* person = *it;

	if (person->name != name || person->addr != addr) return nullptr;
	else return person;
}

/*
	CPerson*	CTaxRegister::FindByAccount	(const string& account) const
	finds CPerson instance in register by provided account number
	returns: CPerson* if instance was found,
					 nullptr otherwise
*/
CPerson*	CTaxRegister::FindByAccount	(const string& account) const
{
	CPerson tmp("", "", account);
	auto it = lower_bound(peopleByAccount.begin(), peopleByAccount.end(), &tmp, compareByAccount);

	if (it == peopleByAccount.end()) return nullptr;
	CPerson* person = *it;
	
	if (person->account != account) return nullptr;
	else return person;
}

/*
	bool	CTaxRegister::Income	(CPerson* person, int amount)
	adds the amount to sumIncome of person
	returns: true if person is not nullptr,
					 false otherwise
*/
bool	CTaxRegister::Income	(CPerson* person, int amount)
{
	if (!person) return false;
	person->sumIncome += amount;
	return true;
}

/*
	bool	CTaxRegister::Expense	(CPerson* person, int amount)
	adds the amount to sumExpense of person
	returns: true if person is not nullptr,
					 false otherwise
*/
bool	CTaxRegister::Expense	(CPerson* person, int amount)
{
	if (!person) return false;
	person->sumExpense += amount;
	return true;
}

/*
	CIterator	CTaxRegister::ListByName	(void) const
	creates CIterator instance over this CTaxRegister instance
	returns: new CIterator instance
*/
CIterator	CTaxRegister::ListByName	(void) const
{
	return CIterator(this);
}

// CTaxRegister destructor
CTaxRegister::~CTaxRegister()
{
	for (auto& person : peopleByName)
		delete person;
}

/*
	bool	CIterator::AtEnd	(void) const
	checks if CIterator is at the end of registers vector of CPerson objects
	returns: true if CIterator is at the end of registers peopleByName vector,
					 false otherwise
*/
bool	CIterator::AtEnd	(void) const
{
	return index == reg->peopleByName.size();
}

/*
	void	CIterator::Next	(void)
	index incrementation in CIterator
*/
void	CIterator::Next	(void)
{
	index++;
}

/*
	string	CIterator::Name	(void) const
	returns: string with name at index in register
*/
string	CIterator::Name	(void) const
{
	return reg->peopleByName[index]->name;
}

/*
	string	CIterator::Addr	(void) const
	returns: string with address at index in register
*/
string	CIterator::Addr	(void) const
{
	return reg->peopleByName[index]->addr;
}

/*
	string	CIterator::Account	(void) const
	returns: string with account number at index in register
*/
string	CIterator::Account	(void) const
{
	return reg->peopleByName[index]->account;
}

#ifndef __PROGTEST__
int main ( void )
{
  string acct;
  int    sumIncome, sumExpense;
  CTaxRegister b1;
  assert ( b1 . Birth ( "John Smith", "Oak Road 23", "123/456/789" ) );
  assert ( b1 . Birth ( "Jane Hacker", "Main Street 17", "Xuj5#94" ) );
  assert ( b1 . Birth ( "Peter Hacker", "Main Street 17", "634oddT" ) );
  assert ( b1 . Birth ( "John Smith", "Main Street 17", "Z343rwZ" ) );
  assert ( b1 . Income ( "Xuj5#94", 1000 ) );
  assert ( b1 . Income ( "634oddT", 2000 ) );
  assert ( b1 . Income ( "123/456/789", 3000 ) );
  assert ( b1 . Income ( "634oddT", 4000 ) );
  assert ( b1 . Income ( "Peter Hacker", "Main Street 17", 2000 ) );
  assert ( b1 . Expense ( "Jane Hacker", "Main Street 17", 2000 ) );
  assert ( b1 . Expense ( "John Smith", "Main Street 17", 500 ) );
  assert ( b1 . Expense ( "Jane Hacker", "Main Street 17", 1000 ) );
  assert ( b1 . Expense ( "Xuj5#94", 1300 ) );
  assert ( b1 . Audit ( "John Smith", "Oak Road 23", acct, sumIncome, sumExpense ) );
  assert ( acct == "123/456/789" );
  assert ( sumIncome == 3000 );
  assert ( sumExpense == 0 );
  assert ( b1 . Audit ( "Jane Hacker", "Main Street 17", acct, sumIncome, sumExpense ) );
  assert ( acct == "Xuj5#94" );
  assert ( sumIncome == 1000 );
  assert ( sumExpense == 4300 );
  assert ( b1 . Audit ( "Peter Hacker", "Main Street 17", acct, sumIncome, sumExpense ) );
  assert ( acct == "634oddT" );
  assert ( sumIncome == 8000 );
  assert ( sumExpense == 0 );
  assert ( b1 . Audit ( "John Smith", "Main Street 17", acct, sumIncome, sumExpense ) );
  assert ( acct == "Z343rwZ" );
  assert ( sumIncome == 0 );
  assert ( sumExpense == 500 );
  CIterator it = b1 . ListByName ();
  assert ( ! it . AtEnd ()
           && it . Name () == "Jane Hacker"
           && it . Addr () == "Main Street 17"
           && it . Account () == "Xuj5#94" );
  it . Next ();
  assert ( ! it . AtEnd ()
           && it . Name () == "John Smith"
           && it . Addr () == "Main Street 17"
           && it . Account () == "Z343rwZ" );
  it . Next ();
  assert ( ! it . AtEnd ()
           && it . Name () == "John Smith"
           && it . Addr () == "Oak Road 23"
           && it . Account () == "123/456/789" );
  it . Next ();
  assert ( ! it . AtEnd ()
           && it . Name () == "Peter Hacker"
           && it . Addr () == "Main Street 17"
           && it . Account () == "634oddT" );
  it . Next ();
  assert ( it . AtEnd () );

  assert ( b1 . Death ( "John Smith", "Main Street 17" ) );

  CTaxRegister b2;
  assert ( b2 . Birth ( "John Smith", "Oak Road 23", "123/456/789" ) );
  assert ( b2 . Birth ( "Jane Hacker", "Main Street 17", "Xuj5#94" ) );
  assert ( !b2 . Income ( "634oddT", 4000 ) );
  assert ( !b2 . Expense ( "John Smith", "Main Street 18", 500 ) );
  assert ( !b2 . Audit ( "John Nowak", "Second Street 23", acct, sumIncome, sumExpense ) );
  assert ( !b2 . Death ( "Peter Nowak", "5-th Avenue" ) );
  assert ( !b2 . Birth ( "Jane Hacker", "Main Street 17", "4et689A" ) );
  assert ( !b2 . Birth ( "Joe Hacker", "Elm Street 23", "Xuj5#94" ) );
  assert ( b2 . Death ( "Jane Hacker", "Main Street 17" ) );
  assert ( b2 . Birth ( "Joe Hacker", "Elm Street 23", "Xuj5#94" ) );
  assert ( b2 . Audit ( "Joe Hacker", "Elm Street 23", acct, sumIncome, sumExpense ) );
  assert ( acct == "Xuj5#94" );
  assert ( sumIncome == 0 );
  assert ( sumExpense == 0 );
  assert ( !b2 . Birth ( "Joe Hacker", "Elm Street 23", "AAj5#94" ) );

  return 0;
}
#endif /* __PROGTEST__ */
