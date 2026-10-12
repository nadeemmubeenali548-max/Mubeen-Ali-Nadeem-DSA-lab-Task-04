#include <iostream>
#include <string>
using namespace std;

// Part B - Individual Project
// Real-world problem: Campus Emergency Maintenance Request System
// Some maintenance requests are more urgent than others and must be solved first.
// Priority 1 = Critical emergency, 2 = Academic support, 3 = Routine maintenance

struct MaintenanceRequestNode
{
    int requestID;
    string requesterName;
    string location;
    string issueType;
    int priority;
    MaintenanceRequestNode* next;
};

class PriorityQueue
{
private:
    MaintenanceRequestNode* front;
    MaintenanceRequestNode* rear;
    int count;

public:
    PriorityQueue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    ~PriorityQueue()
    {
        while (front != nullptr)
        {
            MaintenanceRequestNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        count = 0;
    }

    void Add(MaintenanceRequestNode* request)
    {
        request->next = nullptr;

        if (front == nullptr)
        {
            front = request;
            rear = request;
        }
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        else
        {
            MaintenanceRequestNode* current = front;

            while (current->next != nullptr && current->next->priority <= request->priority)
            {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == nullptr)
            {
                rear = request;
            }
        }

        count++;
    }

    MaintenanceRequestNode* Remove()
    {
        if (front == nullptr)
            return nullptr;

        MaintenanceRequestNode* request = front;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        request->next = nullptr;
        count--;
        return request;
    }

    bool IsEmpty()
    {
        return front == nullptr;
    }

    bool IsNotEmpty()
    {
        return front != nullptr;
    }

    void PrintQueue()
    {
        if (front == nullptr)
        {
            cout << "No requests in the queue." << endl;
            return;
        }

        MaintenanceRequestNode* current = front;
        cout << "Front -> ";

        while (current != nullptr)
        {
            cout << current->requesterName << " (P" << current->priority << ")";
            if (current->next != nullptr)
                cout << " -> ";
            current = current->next;
        }

        cout << " -> Rear" << endl;
    }
};

MaintenanceRequestNode* CreateRequest(int requestID, string requesterName, string location, string issueType, int priority)
{
    MaintenanceRequestNode* request = new MaintenanceRequestNode;
    request->requestID = requestID;
    request->requesterName = requesterName;
    request->location = location;
    request->issueType = issueType;
    request->priority = priority;
    request->next = nullptr;
    return request;
}

void DisplayRequest(MaintenanceRequestNode* request)
{
    cout << "Request ID: " << request->requestID << endl;
    cout << "Requester: " << request->requesterName << endl;
    cout << "Location: " << request->location << endl;
    cout << "Issue Type: " << request->issueType << endl;
    cout << "Priority: " << request->priority << endl;
    cout << "--------------------------------" << endl;
}

int main()
{
    cout << "============================================" << endl;
    cout << "Campus Emergency Maintenance Request System" << endl;
    cout << "============================================" << endl;

    // Example real project data
    PriorityQueue maintenanceQueue;

    maintenanceQueue.Add(CreateRequest(101, "Ali", "Computer Lab 3", "Power failure", 3));
    maintenanceQueue.Add(CreateRequest(102, "Ahmed", "Main Hall", "Fire alarm issue", 1));
    maintenanceQueue.Add(CreateRequest(103, "Bilal", "Library", "Projector not working", 2));
    maintenanceQueue.Add(CreateRequest(104, "Hamza", "Engineering Block", "Air conditioner issue", 1));

    cout << "\nPending requests before processing:" << endl;
    maintenanceQueue.PrintQueue();

    cout << "\nProcessing requests in priority order:" << endl;
    int requestCounter = 1;
    while (!maintenanceQueue.IsEmpty())
    {
        MaintenanceRequestNode* processed = maintenanceQueue.Remove();
        cout << requestCounter << ". Processed: " << processed->requesterName
             << " (Priority " << processed->priority << ") - "
             << processed->issueType << endl;
        requestCounter++;
        delete processed;
    }

    cout << "All maintenance requests have been processed." << endl;
    return 0;
}