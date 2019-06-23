package graphics;

import javax.swing.*;
import java.awt.*;

public class VirtualPiano extends JFrame {
    private static final int DEFAULT_WIDTH = 1024, DEFAULT_HEIGHT = 256;

    private JPanel mainPanel = new JPanel();

    private JPanel whiteKeysPanel = new JPanel(new GridLayout());
    private JPanel blackKeysPanel = new JPanel(new GridLayout());

    private void setWhiteKeys() {

    }

    private void setBlackKeys() {

    }

    public VirtualPiano() throws HeadlessException {
        super("Virtual Piano");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setMinimumSize(new Dimension(DEFAULT_WIDTH, DEFAULT_HEIGHT));
        this.add(this.mainPanel);
        this.pack();
        this.setVisible(true);
    }

    public static void main(String ... args) {
        new VirtualPiano();
    }

}
