*This project has been created as part of the 42 curriculum by vnaoussi.*

# Minitalk

## Description

Minitalk is a small data exchange program utilizing UNIX signals to establish communication between a client and a server. The objective is to create a robust messaging system where data is transmitted exclusively using `SIGUSR1` and `SIGUSR2` signals.

## Project Description: Technical Choices

### Signal Handling: `signal` vs `sigaction`

For handling UNIX signals, two primary methods are available in C: the legacy `signal` function and the more modern `sigaction`. **`sigaction`** was chosen for this project due to its reliability and extended capabilities required for the mandatory and bonus parts.

#### `signal`
*   **Pros:**
    *   **Simplicity:** Very easy to implement with a simple function pointer syntax.
*   **Cons:**
    *   **Portability Issues:** Behavior varies significantly between UNIX systems (System V vs BSD).
    *   **Lack of Context:** Does not provide information about the sender of the signal (like the PID), which is critical for the bonus part of this project.

#### `sigaction`
*   **Pros:**
    *   **Standardization:** POSIX compliant, ensuring consistent behavior across systems.
    *   **Extended Context (`siginfo_t`):** Allows access to metadata about the signal, specifically the **Sender PID**. This is essential for the server to send an acknowledgement signal back to the client.
    *   **Blocking:** Allows explicit blocking of other signals while the handler is executing, preventing race conditions.
*   **Cons:**
    *   **Verbosity:** Requires defining a `struct sigaction` and setting flags, making the setup more verbose.

### Data Transmission: Bitwise Operations

Since communication is restricted to only two signals (`SIGUSR1` and `SIGUSR2`), we cannot transfer data types like `char` or `int` directly. We must implement a binary protocol.

#### Fundamental Bitwise Operations

*   **Left Shift (`<<`)**: `1 << 3` shifts the bit `1` three positions to the left (`00000001` -> `00001000`). Used to create bitmasks.
*   **Right Shift (`>>`)**: `c >> 3` shifts all bits of `c` to the right. Used to isolate a specific bit by moving it to the 0th position.
*   **Bitwise AND (`&`)**: Compares two bits. Returns `1` only if both are `1`. Used to check the value of a specific bit.
*   **Bitwise OR (`|`)**: Returns `1` if at least one bit is `1`. Used to set a specific bit to `1`.

#### How it works in Minitalk

*   **Client Side (Reading)**: `(c >> bit) & 1`
    1.  The bit at position `bit` is moved to position 0.
    2.  `& 1` checks if that bit is `1` or `0`.
    3.  `SIGUSR2` is sent for `1`, `SIGUSR1` for `0`.
*   **Server Side (Reconstructing)**: `c |= (1 << (7 - bits))`
    1.  A mask is created with a `1` at the current bit position.
    2.  `|=` sets that bit to `1` in the character `c` if `SIGUSR2` was received.

---

## Instructions

### 1. Compilation

The project is compiled using a `Makefile`.

*   **Mandatory Part:**
    ```bash
    make
    ```
    Generates `server` and `client`.

*   **Bonus Part:**
    ```bash
    make bonus
    ```
    Generates `server_bonus` and `client_bonus` (supports acknowledgements).

*   **Cleaning:**
    ```bash
    make fclean
    ```

### 2. Starting the Server

The server must be started first to obtain its Process ID (PID).

```bash
./server
```
*Output example:*
```
PID: 4242
```

### 3. Running the Client

In a separate terminal, run the client using the Server's PID and the message to send.

```bash
./client 4242 "Hello, Minitalk!"
```

The server should immediately display:
```
Hello, Minitalk!
```

---

## Bonus Part

The bonus implementation includes additional features for reliability and versatility:

*   **Acknowledgement (Ping-Pong):** The server sends a signal back to the client after receiving every message (or bit/byte depending on implementation). This ensures the client knows the server is ready for the next chunk of data, making the transmission much more reliable than using simple `usleep`.
*   **Unicode Support:** Since the protocol transmits raw bytes (octets), UTF-8 characters (like emojis 🚀 or accented letters `é`) are naturally supported. The server reconstructs the multibyte characters byte-by-byte and prints them correctly.

---

## AI Usage

Artificial Intelligence was used to assist in generating the structure of this README and providing comparative analysis between technical choices (like `signal` vs `sigaction`) to better understand the underlying mechanisms required by the subject.

---

## Resources

*   [man sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html)
*   [man kill](https://man7.org/linux/man-pages/man2/kill.2.html)
*   [UNIX Signals](https://en.wikipedia.org/wiki/Signal_(IPC))

---