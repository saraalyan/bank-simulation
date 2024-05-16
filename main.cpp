#include <iostream>
#include <queue>

using namespace std;
struct client {
    string name;
    int client_time;
    string client_type;
    int service_time;
    int waiting_time;
    bool isVIP;
};

struct compareclienttime {
    bool operator()(const client& c1, const client& c2) const {
        if (c1.client_time == c2.client_time) {
            return c1.isVIP < c2.isVIP;
        }

        return c1.client_time > c2.client_time;
    }
};

class bank {
private:
    priority_queue<client, vector<client>, compareclienttime> client_queue;
    queue<client> bankqueue;
    int current_time = 0;
    int teller_num = 3;
    int total_clients_served = 0;
    int initial_client_service_time = 0;
    int last_client_service_end_time = 0;
    int total_waiting_time = 0;
    int total_service_time = 0;
    int total_service_time_per_teller = 0;

public:
    int getTellerNum() const {
        return teller_num;
    }

    void setTellerNum(int num) {
        teller_num = num;
    }

    void addClient(client c) {
        client_queue.push(c);
        initial_client_service_time = c.service_time;
    }

    void addqueuebank(client c) {
        c.waiting_time = current_time - c.client_time;
        bankqueue.push(c);
    }

    client getNextClient() {
        client next_client = client_queue.top();
        client_queue.pop();
        return next_client;
    }

    void runBank(int simulation_duration) {
        int end_time = current_time + simulation_duration;

        cout << "Running simulation..." << endl;

        while (current_time < end_time || !client_queue.empty() || !bankqueue.empty()) {
            if (!client_queue.empty()) {
                client next_client = getNextClient();
                current_time = max(current_time, next_client.client_time);
                if (next_client.client_type == "exit") {

                    cout << "[" << current_time << "] Adding event: " << next_client.name
                         << ",leaving Time: " << current_time << ",Service Time:: " << next_client.service_time
                         << ", Waiting time: " << next_client.waiting_time
                         << ", Event type: " << next_client.client_type
                         << endl;

                    total_service_time_per_teller += next_client.service_time;
                }
                if (next_client.client_type == "arrival") {
                    if (teller_num > 0) {
                        next_client.client_time += next_client.service_time;
                        next_client.client_type = "exit";
                        total_clients_served++;
                        addClient(next_client);
                        teller_num--;
                    }
                    else {
                        addqueuebank(next_client);
                    }
                }
                else if (next_client.client_type == "exit") {
                    if (!bankqueue.empty()) {
                        client next_bank_client = bankqueue.front();
                        bankqueue.pop();
                        next_bank_client.waiting_time = current_time - next_bank_client.client_time;
                        next_bank_client.client_time = current_time + next_bank_client.service_time;
                        next_bank_client.client_type = "exit";
                        addClient(next_bank_client);
                        total_clients_served++;
                    }
                    else {
                        teller_num++;
                    }
                }

                total_waiting_time += next_client.waiting_time;
                total_service_time += next_client.service_time;
                last_client_service_end_time = next_client.client_time + next_client.service_time;
            }
        }

        printFinalMetrics();
    }
    void printFinalMetrics() {
        double average_waiting_time = (double)total_waiting_time / total_clients_served;
        double average_service_time = (double)total_service_time / total_clients_served;
        double average_service_time_per_teller = (double)total_service_time_per_teller / (teller_num + 3);

        int total_active_service_time = last_client_service_end_time - teller_num * initial_client_service_time;
        double teller_utilization_rate = (double)total_active_service_time / last_client_service_end_time;

        cout << "Total Clients Served: " << total_clients_served << endl;
        cout << "Average Waiting Time: " << average_waiting_time << " minutes" << endl;
        // cout << "Average Service Time: " << average_service_time << " minutes" << endl;
        // cout << "Average Service Time  " << average_service_time_per_teller << " minutes" << endl;
        // cout << "Teller Utilization Rate: " << teller_utilization_rate * 100 << "%" << endl;
        }

    bool isEmpty() {
        return client_queue.empty();
    }
};

int main() {
    bank b1;
    client c1, c2, c3, c4, c5, c6, c7,c8,c9;
    c1.name = "c1";
    c1.client_type = "arrival";
    c1.client_time = 35;
    c1.service_time = 62;
    c1.waiting_time = 0;
    c1.isVIP = false;

    c2.name = "c2";
    c2.client_type = "arrival";
    c2.client_time = 39;
    c2.service_time = 57;
    c2.waiting_time = 0;
    c2.isVIP = 0;


    c3.name = "c3";
    c3.client_type = "arrival";
    c3.client_time = 78;
    c3.service_time = 124;
    c3.waiting_time = 0;
    c3.isVIP = false;

    c4.name = "c4";
    c4.client_type = "arrival";
    c4.client_time = 80;
    c4.service_time = 50;
    c4.waiting_time = 0;
    c4.isVIP = false;

    c5.name = "c5";
    c5.client_type = "arrival";
    c5.client_time = 82;
    c5.service_time = 55;
    c5.waiting_time = 0;
    c5.isVIP = true;

    c6.name = "c6";
    c6.client_type = "arrival";
    c6.client_time = 85;
    c6.service_time = 60;
    c6.waiting_time = 0;
    c6.isVIP = false;



    c7.name = "c7";
    c7.client_type = "arrival";
    c7.client_time = 88;
    c7.service_time = 50;
    c7.waiting_time = 0;
    c7.isVIP = true;


    c8.name = "c8";
    c8.client_type = "arrival";
    c8.client_time = 89;
    c8.service_time = 59;
    c8.waiting_time = 0;
    c8.isVIP = true;


    c9.name = "c9";
    c9.client_type = "arrival";
    c9.client_time = 95;
    c9.service_time = 63;
    c9.waiting_time = 0;
    c9.isVIP = false;



    b1.addClient(c1);
    b1.addClient(c2);
    b1.addClient(c3);
    b1.addClient(c4);
    b1.addClient(c5);
    b1.addClient(c6);
    b1.addClient(c7);

    b1.addClient(c8);
    b1.addClient(c9);
    b1.runBank(200);

}
