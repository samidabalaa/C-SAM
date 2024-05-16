import java.util.Scanner;

public class BankManagementSystem {
    private static final int ACCOUNT_NUMBER_DIGITS = 8;
    private static final double MAX_CASH_INFLOW = 1000000.0;
    private static final double INTEREST_RATE = 0.02;
    private static final double MAX_CASH_WITHDRAW = 10000.0;

    private int accountNumber;
    private double balance;
    private boolean calculateInterest; // Added variable to track user's interest preference

    public BankManagementSystem(int accountNumber, double initialBalance) {
        this.accountNumber = accountNumber;
        this.balance = initialBalance;
        this.calculateInterest = true; // Assume interest calculation is enabled by default
    }

    public void setCalculateInterest(boolean calculateInterest) {
        this.calculateInterest = calculateInterest;
    }

    public void deposit(double amount) {
        if (amount > 0 && (balance + amount) <= MAX_CASH_INFLOW) {
            balance += amount;
            System.out.println("Deposit successful. New balance: " + balance);
        } else {
            System.out.println("Invalid deposit amount or exceeding maximum cash inflow limit.");
        }
    }

    public void withdraw(double amount) {
        if (amount > 0 && amount <= balance && amount<=MAX_CASH_WITHDRAW ) {
            balance -= amount;
            System.out.println("Withdrawal successful. New balance: " + balance);
        } else {
            System.out.println("Invalid withdrawal amount or insufficient balance.");
        }
    }

    public void calculateInterest() {
        if (calculateInterest) {
            double interest = balance * INTEREST_RATE;
            balance += interest;
            System.out.println("Interest calculated and added. New balance: " + balance);
        } else {
            System.out.println("Interest calculation is disabled by user.");
        }
    }

    public void displayBalance() {
        System.out.println("Account Number: " + accountNumber);
        System.out.println("Current Balance: " + balance);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Get user input for account number and initial balance
        System.out.print("Enter your 8-digit account number: ");
        int accountNumber = scanner.nextInt();

        System.out.print("Enter your initial balance: ");
        double initialBalance = scanner.nextDouble();

        // Create CoolBank object
        BankManagementSystem coolBank = new BankManagementSystem(accountNumber, initialBalance);

        // Main menu
        int choice;
        do {
            System.out.println("\n=== BankManagementSystem Menu ===");
            System.out.println("1. Deposit");
            System.out.println("2. Withdraw");
            System.out.println("3. Toggle Interest Calculation On/Off");
            System.out.println("4. Calculate Interest");
            System.out.println("5. Display Balance");
            System.out.println("0. Exit");

            System.out.print("Enter your choice: ");
            choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Enter deposit amount: ");
                    double depositAmount = scanner.nextDouble();
                    coolBank.deposit(depositAmount);
                    break;
                case 2:
                    System.out.print("Enter withdrawal amount: ");
                    double withdrawalAmount = scanner.nextDouble();
                    coolBank.withdraw(withdrawalAmount);
                    break;
                case 3:
                    System.out.print("Do you want to enable interest calculation? (true/false): ");
                    boolean enableInterest = scanner.nextBoolean();
                    coolBank.setCalculateInterest(enableInterest);
                    System.out.println("Interest calculation is now " + (enableInterest ? "enabled." : "disabled."));
                    break;
                case 4:
                    coolBank.calculateInterest();
                    break;
                case 5:
                    coolBank.displayBalance();
                    break;
                case 0:
                    System.out.println("Exiting CoolBank. Thank you!");
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        } while (choice != 0);

        scanner.close();
    }
}


