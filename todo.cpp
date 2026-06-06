#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Task
{
private:
    string title;
    string category;
    bool completed;

public:
    // Constructor
    Task(const string &title, const string &category)
    {
        this->title = title;
        this->category = category;
        this->completed = false;
    }

    // Getters
    string getTitle() const
    {
        return title;
    }
    string getCategory() const
    {
        return category;
    }
    bool isCompleted() const
    {
        return completed;
    }

    // Mark as done & undone
    void markComplete()
    {
        completed = true;
    }

    void unmarkComplete()
    {
        completed = false;
    }
};

// Save all tasks to a file
void saveTasks(vector<Task> &tasks)
{
    ofstream file("tasks.txt");
    for (size_t i = 0; i < tasks.size(); i++)
    {
        file << tasks[i].getTitle() << "\n"
             << tasks[i].getCategory() << "\n"
             << tasks[i].isCompleted() << "\n";
    }
    file.close();
}

// Load tasks from file
void loadTasks(vector<Task> &tasks)
{
    ifstream file("tasks.txt");
    if (!file.is_open())
        return; // no file yet, that's fine

    string title, category;
    bool completed;

    while (getline(file, title))
    {
        getline(file, category);
        file >> completed;
        file.ignore();

        Task t(title, category);
        if (completed)
            t.markComplete();
        tasks.push_back(t);
    }
    file.close();
}

void saveCategories(vector<string> &categories)
{
    ofstream file("categories.txt");
    for (size_t i = 0; i < categories.size(); i++)
    {
        file << categories[i] << "\n";
    }
    file.close();
}

void loadCategories(vector<string> &categories)
{
    ifstream file("categories.txt");
    if (!file.is_open())
        return;
    categories.clear();
    string cat;
    while (getline(file, cat))
    {
        if (!cat.empty())
            categories.push_back(cat);
    }
    file.close();
}

void displayAllTasks(vector<Task> &tasks)
{
    if (tasks.empty())
    {
        cout << "No tasks found!" << endl;
        return;
    }
    cout << "\n=== All Tasks ===" << endl;
    for (size_t i = 0; i < tasks.size(); i++)
    {
        cout << i + 1 << ". "
             << tasks[i].getTitle()
             << " [" << tasks[i].getCategory() << "]"
             << " - " << (tasks[i].isCompleted() ? "Completed" : "Pending ")
             << endl;
    }
}

int main()
{
    vector<Task> tasks;
    vector<string> categories = {"Work", "Study", "Personal", "Health", "Finance", "Shopping"};

    loadCategories(categories);
    loadTasks(tasks);
    if (tasks.empty())
    {
        cout << "No saved tasks found." << endl;
    }
    else
    {
        cout << tasks.size() << " task(s) loaded successfully" << endl;
    }

    int choice;

    do
    {
        cout << "\n|===      To-Do List     ===|" << endl;
        cout << "| 1. Add Task               |" << endl;
        cout << "| 2. View All Tasks         |" << endl;
        cout << "| 3. Mark Task as Completed |" << endl;
        cout << "| 4. View Pending Tasks     |" << endl;
        cout << "| 5. View Completed Tasks   |" << endl;
        cout << "| 6. Delete Task            |" << endl;
        cout << "| 7. Unmark Task as Pending |" << endl;
        cout << "| 8. Exit                   |" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            choice = 0;
            continue;
        }
        cin.ignore();

        switch (choice)
        {

        case 1:
        {
            string title, category;
            cout << "Enter task title: ";
            getline(cin, title);
            if (title.empty() || title.find_first_not_of(' ') == string::npos)
            {
                cout << "Task title cannot be empty!" << endl;
                break;
            }
            int catChoice;
            cout << "\nSelect Category:" << endl;
            for (size_t i = 0; i < categories.size(); i++)
            {
                cout << i + 1 << ". " << categories[i] << endl;
            }
            cout << categories.size() + 1 << ". + Add New Category" << endl;
            cout << "Enter category number: ";

            while (!(cin >> catChoice) || catChoice < 1 || (size_t)catChoice > categories.size() + 1)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid! Enter a valid number: ";
            }
            cin.ignore();

            if ((size_t)catChoice == categories.size() + 1)
            {
                cout << "Enter new category name: ";
                string newCat;
                getline(cin, newCat);
                if (newCat.empty() || newCat.find_first_not_of(' ') == string::npos)
                {
                    cout << "Invalid category name!" << endl;
                    break;
                }
                categories.push_back(newCat);
                category = newCat;
                saveCategories(categories);
                cout << "Category \"" << newCat << "\" added!" << endl;
            }
            else
            {
                category = categories[catChoice - 1];
            }
            bool duplicate = false;
            for (size_t i = 0; i < tasks.size(); i++)
            {
                if (tasks[i].getTitle() == title)
                {
                    duplicate = true;
                    break;
                }
            }

            if (duplicate)
            {
                cout << "Task \"" << title << "\" already exists." << endl;
            }
            else
            {
                tasks.push_back(Task(title, category));
                cout << "Task added successfully" << endl;
                saveTasks(tasks);
            }
            break;
        }

        case 2:
        {
            displayAllTasks(tasks);
            break;
        }

        case 3:
        {
            if (tasks.empty())
            {
                cout << "No tasks found" << endl;
                break;
            }

            displayAllTasks(tasks);

            cout << "Enter task number to mark complete: ";
            int num;
            cin >> num;
            cin.ignore();
            if (num < 1 || (size_t)num > tasks.size())
            {
                cout << "Invalid task number" << endl;
            }
            else if (tasks[num - 1].isCompleted())
            {
                cout << "Task is already completed" << endl;
            }
            else
            {
                tasks[num - 1].markComplete();
                cout << "Task marked as completed" << endl;
                saveTasks(tasks);
            }
            break;
        }

        case 4:
        {
            cout << "\n=== Pending Tasks ===" << endl;
            int count = 0;
            for (size_t i = 0; i < tasks.size(); i++)
            {
                if (!tasks[i].isCompleted())
                {
                    count++;
                    cout << count << ". "
                         << tasks[i].getTitle()
                         << " [" << tasks[i].getCategory() << "]"
                         << endl;
                }
            }
            if (count == 0)
                cout << "No pending tasks" << endl;
            break;
        }

        case 5:
        {
            cout << "\n=== Completed Tasks ===" << endl;
            int count = 0;
            for (size_t i = 0; i < tasks.size(); i++)
            {
                if (tasks[i].isCompleted())
                {
                    count++;
                    cout << count << ". "
                         << tasks[i].getTitle()
                         << " [" << tasks[i].getCategory() << "]"
                         << endl;
                }
            }
            if (count == 0)
                cout << "No completed tasks" << endl;
            break;
        }

        case 6:
        {
            if (tasks.empty())
            {
                cout << "No tasks found" << endl;
                break;
            }

            displayAllTasks(tasks);

            cout << "Enter task number to delete: ";
            int num;
            cin >> num;
            cin.ignore();
            if (num < 1 || (size_t)num > tasks.size())
            {
                cout << "Invalid task number" << endl;
            }
            else
            {
                cout << "\"" << tasks[num - 1].getTitle() << "\" deleted!" << endl;
                tasks.erase(tasks.begin() + num - 1);
                saveTasks(tasks);
            }
            break;
        }

        case 7:
        {
            if (tasks.empty())
            {
                cout << "No tasks found" << endl;
                break;
            }
            displayAllTasks(tasks);
            cout << "Enter task number to unmark: ";
            int num;
            cin >> num;
            cin.ignore();
            if (num < 1 || (size_t)num > tasks.size())
            {
                cout << "Invalid task number" << endl;
            }
            else if (!tasks[num - 1].isCompleted())
            {
                cout << "Task is already pending" << endl;
            }
            else
            {
                tasks[num - 1].unmarkComplete();
                cout << "Task marked as pending" << endl;
                saveTasks(tasks);
            }
            break;
        }

        case 8:
            saveTasks(tasks);
            cout << "Thanks for using our Todo List" << endl;
            break;

        default:
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 8);

    return 0;
}