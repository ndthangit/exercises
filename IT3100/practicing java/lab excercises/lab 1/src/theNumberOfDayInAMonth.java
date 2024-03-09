import javax.swing.JOptionPane;

public class theNumberOfDayInAMonth {
    public static void main(String args[]) {
        String year, month;
        month = JOptionPane.showInputDialog(null, "Please input the month: ", "Input the month",
                JOptionPane.INFORMATION_MESSAGE);

        year = JOptionPane.showInputDialog(null, "Please input the year: ", "Input the year",
                JOptionPane.INFORMATION_MESSAGE);

        JOptionPane.showMessageDialog(null, "the number of the month: " + theNumberOfDay(month, year),
                "the number of days of the month",
                JOptionPane.INFORMATION_MESSAGE);
        System.exit(0);
    }

    public static int theNumberOfDay(String month, String year) {
        int consideredYear = Integer.parseInt(year);
        switch (month.toLowerCase()) {
            case "january":
            case "jan":
            case "jan.":
            case "1":
            case "march":
            case "mar":
            case "mar.":
            case "3":
            case "may":
            case "5":
            case "july":
            case "jul":
            case "7":
            case "august":
            case "aug.":
            case "aug":
            case "8":
            case "october":
            case "oct":
            case "oct.":
            case "10":
            case "december":
            case "dec":
            case "dec.":
            case "12":
                return 31;
            case "april":
            case "apr":
            case "apr.":
            case "4":
            case "june":
            case "jun":
            case "6":
            case "september":
            case "sept.":
            case "sep":
            case "9":
            case "november":
            case "nov.":
            case "nov":
            case "11":
                return 30;
            case "february":
            case "feb":
            case "feb.":
            case "2":
                if (consideredYear % 4 == 0) {
                    if (consideredYear % 100 == 0 && consideredYear % 400 != 0) {
                        return 28;
                    }
                    return 29;
                }
                return 28;
            default:
                return -1; 
        }
    }

}
