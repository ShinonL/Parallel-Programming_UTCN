import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.MathContext;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Main {
    static List<BigInteger> fibonacciList = Collections.synchronizedList(new ArrayList<>());

    static BigDecimal SQRT_5;
    static BigDecimal PHI;
    static MathContext MC;

    static final int NO_THREADS = 8;
    static final int MAX_N = 1000;
    static final String FILE_NAME = "fibonacci.txt";

    public static void main(String[] args) {
        long startTime = System.currentTimeMillis();

        MC = new MathContext((int) (0.2 * MAX_N + 100));
        SQRT_5 = BigDecimal.valueOf(5).sqrt(MC);
        PHI = BigDecimal.ONE.add(Main.SQRT_5).divide(BigDecimal.TWO, MC);

        List<ThreadRunner> threadRunners = new ArrayList<>();

        for (int i = 0; i < NO_THREADS; i++) {
            ThreadRunner threadRunner = new ThreadRunner(i);
            threadRunner.start();
            threadRunners.add(threadRunner);
        }

        try {
            for (ThreadRunner threadRunner: threadRunners) {
                threadRunner.join();
            }
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        long endTime = System.currentTimeMillis();
        System.out.println("Execution time: " + (endTime - startTime));

        Collections.sort(fibonacciList);

        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME, false));
            writer.write("");

            for (int i = 0; i <= MAX_N; i++) {
                String str = String.format("F(" + i + ") = " + fibonacciList.get(i).toString());
                writer.append(str);
                writer.append("\r\n");
            }
            writer.close();
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }
}