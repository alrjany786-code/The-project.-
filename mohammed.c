c'''
#include <stdio.h>
#include <string.h>

#define MAX 100

// ===== الهيكل =====
struct Account {
    int id;
    char name[50];
    float balance;
};

struct Account accounts[MAX];
int count = 0;

// ===== البحث عن حساب =====
int findAccount(int id) {
    for (int i = 0; i < count; i++) {
        if (accounts[i].id == id)
            return i;
    }
    return -1;
}

// ===== إنشاء حساب =====
void createAccount() {
    if (count >= MAX) {
        printf("النظام ممتلئ!\n");
        return;
    }
    printf("أدخل رقم الحساب: ");
    scanf("%d", &accounts[count].id);

    if (findAccount(accounts[count].id) != -1) {
        printf("خطأ: رقم الحساب موجود مسبقاً!\n");
        return;
    }

    printf("أدخل اسم العميل: ");
    scanf("%s", accounts[count].name);
    printf("أدخل الرصيد الابتدائي: ");
    scanf("%f", &accounts[count].balance);

    if (accounts[count].balance < 0) {
        printf("خطأ: الرصيد لا يمكن أن يكون سالباً!\n");
        return;
    }

    count++;
    printf("تم إنشاء الحساب بنجاح!\n");
}

// ===== عرض بيانات حساب =====
void showAccount() {
    int id;
    printf("أدخل رقم الحساب: ");
    scanf("%d", &id);

    int index = findAccount(id);
    if (index == -1) {
        printf("خطأ: الحساب غير موجود!\n");
        return;
    }

    printf("\n--- بيانات الحساب ---\n");
    printf("رقم الحساب : %d\n", accounts[index].id);
    printf("اسم العميل : %s\n", accounts[index].name);
    printf("الرصيد     : %.2f دينار\n", accounts[index].balance);
}

// ===== إيداع =====
void deposit() {
    int id;
    float amount;

    printf("أدخل رقم الحساب: ");
    scanf("%d", &id);

    int index = findAccount(id);
    if (index == -1) {
        printf("خطأ: الحساب غير موجود!\n");
        return;
    }

    printf("أدخل مبلغ الإيداع: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("خطأ: يجب أن يكون المبلغ أكبر من الصفر!\n");
        return;
    }

    accounts[index].balance += amount;
    printf("تم الإيداع بنجاح. الرصيد الجديد: %.2f دينار\n",
           accounts[index].balance);
}

// ===== سحب =====
void withdraw() {
    int id;
    float amount;

    printf("أدخل رقم الحساب: ");
    scanf("%d", &id);

    int index = findAccount(id);
    if (index == -1) {
        printf("خطأ: الحساب غير موجود!\n");
        return;
    }

    printf("أدخل مبلغ السحب: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("خطأ: يجب أن يكون المبلغ أكبر من الصفر!\n");
        return;
    }

    if (amount > accounts[index].balance) {
        printf("خطأ: الرصيد غير كافٍ! رصيدك: %.2f دينار\n",
               accounts[index].balance);
        return;
    }

    accounts[index].balance -= amount;
    printf("تم السحب بنجاح. الرصيد المتبقي: %.2f دينار\n",
           accounts[index].balance);
}

// ===== تحويل =====
void transferMoney() {
    int fromId, toId;
    float amount;

    printf("أدخل رقم الحساب المُرسِل: ");
    scanf("%d", &fromId);
    printf("أدخل رقم الحساب المُستقبِل: ");
    scanf("%d", &toId);

    int fromIdx = findAccount(fromId);
    int toIdx   = findAccount(toId);

    if (fromIdx == -1 || toIdx == -1) {
        printf("خطأ: أحد الحسابين غير موجود!\n");
        return;
    }

    if (fromId == toId) {
        printf("خطأ: لا يمكن التحويل لنفس الحساب!\n");
        return;
    }

    printf("أدخل المبلغ المراد تحويله: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("خطأ: مبلغ غير صالح!\n");
        return;
    }

    if (amount > accounts[fromIdx].balance) {
        printf("خطأ: رصيد الحساب المُرسِل غير كافٍ!\n");
        return;
    }

    accounts[fromIdx].balance -= amount;
    accounts[toIdx].balance   += amount;

    printf("تم التحويل بنجاح.\n");
    printf("رصيد حساب %d: %.2f دينار\n", fromId, accounts[fromIdx].balance);
    printf("رصيد حساب %d: %.2f دينار\n", toId,   accounts[toIdx].balance);
}

// ===== عرض جميع الحسابات =====
void listAccounts() {
    if (count == 0) {
        printf("لا توجد حسابات مسجلة في النظام.\n");
        return;
    }

    printf("\n%-10s %-20s %-15s\n", "الرقم", "الاسم", "الرصيد");
    printf("------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10d %-20s %-15.2f\n",
               accounts[i].id,
               accounts[i].name,
               accounts[i].balance);
    }

    printf("------------------------------------------\n");
    printf("إجمالي الحسابات: %d\n", count);
}

// ===== حذف حساب =====
void deleteAccount() {
    int id;
    printf("أدخل رقم الحساب المراد حذفه: ");
    scanf("%d", &id);

    int index = findAccount(id);
    if (index == -1) {
        printf("خطأ: الحساب غير موجود!\n");
        return;
    }

    for (int i = index; i < count - 1; i++) {
        accounts[i] = accounts[i + 1];
    }

    count--;
    printf("تم حذف الحساب بنجاح.\n");
}

// ===== الدالة الرئيسية =====
int main() {
    int choice;

    printf("=== نظام إدارة الحسابات البنكية ===\n");

    while (1) {
        printf("\n1. إنشاء حساب جديد\n");
        printf("2. عرض بيانات حساب\n");
        printf("3. إيداع أموال\n");
        printf("4. سحب أموال\n");
        printf("5. تحويل الأموال\n");
        printf("6. عرض جميع الحسابات\n");
        printf("7. حذف حساب\n");
        printf("8. الخروج\n");
        printf("اختر العملية: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount();  break;
            case 2: showAccount();    break;
            case 3: deposit();        break;
            case 4: withdraw();       break;
            case 5: transferMoney();  break;
            case 6: listAccounts();   break;
            case 7: deleteAccount();  break;
            case 8:
                printf("شكراً لاستخدامك النظام. مع السلامة!\n");
                return 0;
            default:
                printf("خيار غير صحيح! اختر من 1 إلى 8.\n");
        }
    }

    return 0;
    
}
        
