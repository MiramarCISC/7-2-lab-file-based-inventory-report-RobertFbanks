#include "inventory_report.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;
// Forgot to add in.close() and out.close() in video, its here now.

bool isValidQuantity(int quantity) {
    // Return true when quantity is 0 or greater.
    return quantity >= 0;
}

bool isValidPrice(double price) {
    // Return true when price is 0 or greater.
    return price >= 0;
}

double calculateItemValue(const InventoryItem& item) {
    // Return quantity multiplied by price.
    // If quantity or price is invalid, return 0.0.
    if (!isValidQuantity(item.quantity) || !isValidPrice(item.price)){
        return 0.0;
    }
    else {
        return (item.quantity * item.price);
    }
}

int readInventoryFile(string filename, InventoryItem items[], int maxItems) {
    // Open the input file.
    // Read records in this format: sku name quantity price
    // Store valid records in the items array.
    // Stop when the file ends or maxItems is reached.
    // Return the number of records stored.
    ifstream in(filename);
    if (!in.is_open()) {
        return 0;
    }
    
    int count = 0;

    while (count < maxItems &&
        in  >> items[count].sku
            >> items[count].name
            >> items[count].quantity
            >> items[count].price) {
    count++;
    }
    in.close();
    return count;
    
}

bool writeInventoryReport(string filename, const InventoryItem items[], int count) {
    // Open the output file.
    // Write each item and its total value.
    // Write the total inventory value.
    // Return true if the report was written successfully.
    ofstream out(filename);

    if (!out.is_open()) {
        return false;
    }
    for (int i = 0; i < count; i++) {
        out << items[i].sku << " "
            << items[i].name << " "
            << items[i].quantity << " "
            << items[i].price << " "
            << calculateItemValue(items[i]) << endl;
    }
    out << "Total inventory value: " // Instructions never said to add the text, was a big headache trying to figure out why my make test wasn't working.
        << calculateTotalInventoryValue(items, count);
        out.close();
    return true;
}

double calculateTotalInventoryValue(const InventoryItem items[], int count) {
    // Return the sum of all item values.
    // Return 0.0 for null arrays or invalid counts.
    if (items == nullptr || count <= 0) {
        return 0.0;
    }

    double total = 0.0;

    for (int i = 0; i < count; i++) {
        total += calculateItemValue(items[i]);
    }

    return total;
}

int findItemBySku(const InventoryItem items[], int count, string sku) {
    // Search for a matching SKU.
    // Return the index if found.
    // Return -1 if not found.
    if (items == nullptr || count <= 0) {
        return -1;
    }
    for (int i = 0; i < count; i++) {
        if (items[i].sku == sku) {
            return i;
        }
    }
    return -1;
}

int findHighestValueItemIndex(const InventoryItem items[], int count) {
    // Return the index of the item with the highest item value.
    // Return -1 for null arrays or invalid counts.
    if (items == nullptr || count <= 0) {
        return -1;
    }
    int highesti = 0;

    for (int i = 1; i < count; i++) {
        if (calculateItemValue(items[i]) > calculateItemValue(items[highesti])) {
            highesti = i;
        }
    }

    return highesti;
}
