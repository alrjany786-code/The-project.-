c'''
#include <stdio.h>

int main() {
    float balance = 1000.0; // الرصيد المبدئي لحساب المستخدم
    int choice;
    float amount;

    printf("=== نظام إدارة الحساب البنكي البسيط ===\n");

    while (1) {
        // عرض قائمة الخيارات للمستخدم
        printf("\n1. عرض الرصيد الحركي\n");
        printf("2. إيداع أموال\n");
        printf("3. سحب أموال\n");
        printf("4. الخروج من البرنامج\n");
        printf("اختر العملية التي تريد تنفيذها: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("رصيدك الحالي هو: %.2f دينار\n", balance);
                break;

            case 2:
                printf("أدخل المبلغ المراد إيداعه: ");
                scanf("%f", &amount);
                if (amount > 0) {
                    balance += amount;
                    printf("تم الإيداع بنجاح. رصيدك الجديد: %.2f دينار\n", balance);
                } else {
                    printf("خطأ: يجب أن يكون مبلغ الإيداع أكبر من الصفر!\n");
                }
                break;

            case 3:
                printf("أدخل المبلغ المراد سحبه: ");
                scanf("%f", &amount);
                if (amount > balance) {
                    printf("خطأ: رصيدك الحالي لا يكفي لإتمام هذه العملية!\n");
                } else if (amount <= 0) {
                    printf("خطأ: يجب أن يكون مبلغ السحب أكبر من الصفر!\n");
                } else {
                    balance -= amount;
                    printf("تم السحب بنجاح. رصيدك المتبقي: %.2f دينار\n", balance);
                }
                break;

            case 4:
                printf("شكراً لاستخدامك نظامنا البنكي. مع السلامة!\n");
                return 0; // إنهاء البرنامج بنجاح

            default:
                printf("خيار غير صحيح! الرجاء اختيار رقم من 1 إلى 4.\n");
        }
    }

    return 0;
}
