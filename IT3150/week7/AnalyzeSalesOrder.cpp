/*Data about sales in an e-commerce company (the e-commerce company has several shops) consists a sequence of lines, each line (represents an order) has the following information:
            <CustomerID> <ProductID> <Price> <ShopID> <TimePoint>
in which the customer <CustomerID> buys a product <ProductID> with price <Price> at the shop <ShopID> at the time-point <TimePoint>
<CustomerID>: string of length from 3 to 10
<ProductID>: string of length from 3 to 10
<Price>: a positive integer from 1 to 1000
<ShopID>: string of length from 3 to 10
<TimePoint>: string representing time-point with the format HH:MM:SS (for example, 09:45:20 means the time-point 9 hour 45 minutes 20 seconds)


Perform a sequence of queries of following types:
?total_number_orders: return the total number of orders
?total_revenue: return the total revenue the e-commerce company gets
?revenue_of_shop <ShopID>: return the total revenue the shop <ShopID> gets
?total_consume_of_customer_shop <CustomerID> <ShopID>: return the total revenue the shop <ShopID> sells products to customer <CustomerID>
?total_revenue_in_period <from_time> <to_time>: return the total revenue the e-commerce gets of the period from <from_time> to <to_time> (inclusive)

Input
The input consists of two blocks of data:
The first block is the operational data, which is a sequence of lines (number of lines can be upto 100000), each line contains the information of a submission with above format
The first block is terminated with a line containing the character #
The second block is the query block, which is a sequence of lines (number of lines can be upto 100000), each line is a query described above
The second block is terminated with a line containing the character #

Output
Write in each line, the result of the corresponding query

Example
Input
C001 P001 10 SHOP001 10:30:10
C001 P002 30 SHOP001 12:30:10
C003 P001 40 SHOP002 10:15:20
C001 P001 80 SHOP002 08:40:10
C002 P001 130 SHOP001 10:30:10
C002 P001 160 SHOP003 11:30:20
#
?total_number_orders
?total_revenue
?revenue_of_shop SHOP001
?total_consume_of_customer_shop C001 SHOP001
?total_revenue_in_period 10:00:00 18:40:45
#


Output
6
450
170
40
370
*/
#include<bits/stdc++.h>
using namespace std;

struct Order {
    string customerID;
    string productID;
    int price;
    string shopID;
    string timePoint;
};

int main() {
    vector<Order> orders;
    unordered_map<string, int> shopRevenue;
    unordered_map<string, unordered_map<string, int>> customerShopRevenue;


    int totalRevenue = 0;

    string line;
    while (getline(cin, line) && line != "#") {
        istringstream iss(line);
        Order order;
        iss >> order.customerID >> order.productID >> order.price >> order.shopID >> order.timePoint;

        orders.push_back(order);
        totalRevenue += order.price;

        shopRevenue[order.shopID] += order.price;
        customerShopRevenue[order.customerID][order.shopID] += order.price;
    }
    sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
        return a.timePoint < b.timePoint;
    });

    vector<int> prefixSum(orders.size(), 0);
    prefixSum[0] = orders[0].price;
    for (int i = 1; i < orders.size(); i++) {
        prefixSum[i] = prefixSum[i - 1] + orders[i].price;
    }
    auto findFirstIndex = [&](const string& time) {
        return lower_bound(orders.begin(), orders.end(), time, [](const Order& order, const string& time) {
            return order.timePoint < time;
        }) - orders.begin();
    };

    auto findLastIndex = [&](const string& time) {
        return upper_bound(orders.begin(), orders.end(), time, [](const string& time, const Order& order) {
            return time < order.timePoint;
        }) - orders.begin() - 1;
    };

    while (getline(cin, line) && line != "#") {
        istringstream iss(line);
        string query;
        iss >> query;

        if (query == "?total_number_orders") {
            cout << orders.size() << endl;

        } else if (query == "?total_revenue") {
            cout << totalRevenue << endl;

        } else if (query == "?revenue_of_shop") {
            string shopID;
            iss >> shopID;
            cout << shopRevenue[shopID] << endl;

        } else if (query == "?total_consume_of_customer_shop") {
            string customerID, shopID;
            iss >> customerID >> shopID;
            cout << customerShopRevenue[customerID][shopID] << endl;

        } else if (query == "?total_revenue_in_period") {
            string fromTime, toTime;
            iss >> fromTime >> toTime;

            int start_index = findFirstIndex(fromTime);
            int end_index = findLastIndex(toTime);

            if (start_index <= end_index) {
                int periodRevenue = prefixSum[end_index];
                if (start_index > 0) periodRevenue -= prefixSum[start_index - 1];
                cout << periodRevenue << endl;
            } else {
                cout << 0 << endl;  
            }
                
        }
    }

    return 0;
}

