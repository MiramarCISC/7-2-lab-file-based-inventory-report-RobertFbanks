#include "inventory_report.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

bool isValidQuantity(int quantity) {
    // Returns true when quantity is 0 or greater.
    // can also do return quantitiy >=0; todo requests to return true
    if(quantity >= 0){
        return true;
    }
    return false;
}

bool isValidPrice(double price) {
    // Returns true when price is 0 or greater.
     // can also do return price >=0; todo requests to return true
    if(price >= 0){
        return true;
    }
    return false;
}

double calculateItemValue(const InventoryItem& item) {
    // If quantity or price is invalid, returns 0.0.
    if(!isValidQuantity(item.quantity) || !isValidPrice(item.price)){
        return 0.0;
    } else {
        // Returns quantity multiplied by price.
        return item.quantity * item.price;
    }
}

int readInventoryFile(string filename, InventoryItem items[], int maxItems) {
    // nullptr check
    if (items == nullptr || maxItems <= 0){
        return 0;
    }
    // Opens the input file.
    ifstream in(filename);

    if (!in.is_open()){
        return 0;
    }
    // Declares and initializes count
    int count = 0;
    InventoryItem item;
    // Reads records in this format: sku name quantity price
    while (count < maxItems && 
        in >> 
        item.sku >> 
        item.name >> 
        item.quantity >> 
        item.price) {
        if(isValidQuantity(item.quantity) && isValidPrice(item.price)) {
            // Stores valid records in the items array.
            items[count] = item;
            count++;
        }
    }
    // Stops when the file ends or maxItems is reached.
    in.close(); 
    // Returns the number of records stored.
    return count;
}

bool writeInventoryReport(string filename, const InventoryItem items[], int count) {
    // Returns false for null arrays or invalid counts.
    if (items == nullptr || count <= 0) {
        return false;
    }
    
    // Opens the output file.
    ofstream out(filename);
    if (!out.is_open()){
        return false;
    }

    out << "Inventory Report" << endl;
    out << "SKU Name Quantity Price Value" << endl;
    // Write each item and its total value.
    for (int i = 0; i< count; i++) {
        out << items[i].sku << " "
            << items[i].name << " "
            << items[i].quantity << " "
            << items[i].price << " "
            << calculateItemValue(items[i])
            << endl;
    }
    // Write the total inventory value.
    out << "Total inventory value: "
        << calculateTotalInventoryValue(items, count)
        << endl;

    out.close();
    // Return true if the report was written successfully.
    return true;
}

double calculateTotalInventoryValue(const InventoryItem items[], int count) {
    // Returns 0.0 for null arrays or invalid counts.
    if (items == nullptr || count <= 0){
        return 0.0;
    }
    // Initializes total to sum all item values
    double total = 0.0;
        // loops through item array
        for (int i = 0; i < count; i++) {
           // Adds value of teh current item to the total
            total += calculateItemValue(items[i]);
        }
        // Returns the sum of all item values.
    return total;
}

int findItemBySku(const InventoryItem items[], int count, string sku) {
    // Returns -1 for null arrays or invalid counts.
    if (items == nullptr || count <= 0) {
        return -1;
    }

    for (int i = 0; i < count; i++){
        // Searches for a matching SKU.
        if (items[i].sku == sku){
            // Returns the index if found.
            return i;
        }
    }
    // Returns -1 if not found.
    return -1;
}

int findHighestValueItemIndex(const InventoryItem items[], int count) {
    // Returns -1 for null arrays or invalid counts.
    if (items == nullptr || count <= 0){
        return -1;
    }
    int highestIndex = 0;
    // Searches for highest value in Index
    for (int i =1; i < count; i++) {
        if (calculateItemValue(items[i]) > calculateItemValue(items[highestIndex])) {
            // Returns the index of the item with the highest item value.
            highestIndex = i;
        }
    }
    // Returns -1 for null arrays or invalid counts.
    return highestIndex;
}
