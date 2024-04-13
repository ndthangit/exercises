public class test {

        public static void main(String[] args) {
            int iterations = 100000;
            double startTime, endTime;

            // Using String concatenation
            startTime = System.currentTimeMillis();
            String resultString = "";
            for (int i = 0; i < iterations; i++) {
                resultString += "String";
            }
            endTime = System.currentTimeMillis();
            System.out.println("Time taken with String concatenation: " + (endTime - startTime) + " milliseconds");

            // Using StringBuffer
            startTime = System.currentTimeMillis();
            StringBuffer stringBuffer = new StringBuffer();
            for (int i = 0; i < iterations; i++) {
                stringBuffer.append("String");
            }
            String resultBuffer = stringBuffer.toString();
            endTime = System.currentTimeMillis();
            System.out.println("Time taken with StringBuffer: " + (endTime - startTime) + " milliseconds");
        }


}
