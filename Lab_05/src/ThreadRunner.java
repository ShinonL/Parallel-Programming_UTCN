import java.math.BigDecimal;
import java.math.BigInteger;

public class ThreadRunner implements Runnable {
    private Thread thread;
    private int threadNumber;

    public ThreadRunner(int threadNumber) {
        this.threadNumber = threadNumber;
        this.thread = new Thread(this, String.valueOf(threadNumber));
    }

    @Override
    public void run() {
        for (int currentN = threadNumber; currentN <= Main.MAX_N; currentN += Main.NO_THREADS) {
            BigInteger fibonacciNumber =
                    Main.PHI.pow(currentN).divide(Main.SQRT_5, Main.MC).add(BigDecimal.valueOf(0.5)).toBigInteger();

            Main.fibonacciList.add(fibonacciNumber);
        }
    }

    public void start() {
        thread.start();
    }

    public void join() throws InterruptedException {
        thread.join();
    }
}
