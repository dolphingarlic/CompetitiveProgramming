using UnityEngine;
using System;

public class AI : MonoBehaviour {
    const int SZ = 11;

    private float[,,] potential = new float[SZ, SZ, 4];
    private float[,,] bridge = new float[SZ, SZ, 4];
    private bool[,] upd = new bool[SZ, SZ];

    private int GetColor(int x, int y) {
        if (x < 0 || x >= SZ) return 1;
        if (y < 0 || y >= SZ) return -1;
        return GameManager.instance.color[x, y];
    }

    private float GetPotential(int x, int y, int k, int c) {
        if (x < 0 || y < 0 || x >= SZ || y >= SZ) return 3e4f;
        if (GetColor(x, y) == 0) return potential[x, y, k];
        if (GetColor(x, y) == -c) return 3e4f;
        return potential[x, y, k] - 3e4f;
    }

    private void SetUpd(int x, int y) {
        if (x < 0 || y < 0 || x >= SZ || y >= SZ) return;
        upd[x, y] = true;
    }

    private int CanConnectFarBorder(int n, int m, int c) {
        if (c > 0) { // Player 1
            if (2 * m < SZ - 1) {
                for (int x = 0; x < SZ; x++) {
                    for (int y = 0; y < m; y++) {
                        if (
                            y - x < m - n &&
                            x + y <= n + m &&
                            GetColor(x, y) != 0
                        ) return 2;
                    }
                }
                if (GetColor(n - 1, m) == -c) return 0;
                if (GetColor(n - 1, m - 1) == -c) {
                    if (GetColor(n + 2, m - 1) == -c) return 0;
                    return -1;
                }
                if (GetColor(n + 2, m - 1) == -c) return -2;
            } else {
                for (int x = 0; x < SZ; x++) {
                    for (int y = SZ - 1; y > m; y--) {
                        if (
                            y - x > m - n &&
                            x + y >= n + m &&
                            GetColor(x, y) != 0
                        )
                            return 2;
                    }
                }
                if (GetColor(n + 1, m) == -c) return 0;
                if (GetColor(n + 1, m + 1) == -c) {
                    if (GetColor(n - 2, m + 1) == -c) return 0;
                    return -1;
                }
                if (GetColor(n - 2, m + 1) == -c) return -2;
            }
        } else {
            if (2 * n < SZ - 1) {
                for (int y = 0; y < SZ; y++) {
                    for (int x = 0; x < n; x++) {
                        if (
                            x - y < n - m &&
                            x + y <= n + m &&
                            GetColor(x, y) != 0
                        ) return 2;
                    }
                }
                if (GetColor(n, m - 1) == -c) return 0;
                if (GetColor(n - 1, m - 1) == -c) {
                    if (GetColor(n - 1, m + 2) == -c) return 0;
                    return -1;
                }
                if (GetColor(n - 1, m + 2) == -c) return -2;
            } else {
                for (int y = 0; y < SZ; y++) {
                    for (int x = SZ - 1; x > n; x--) {
                        if (
                            x - y > n - m &&
                            x + y >= n + m &&
                            GetColor(x, y) != 0
                        ) return 2;
                    }
                }
                if (GetColor(n, m + 1) == -c) return 0;
                if (GetColor(n + 1, m + 1) == -c) {
                    if (GetColor(n + 1, m - 2) == -c) return 0;
                    return -1;
                }
                if (GetColor(n + 1, m - 2) == -c) return -2;
            }
        }
        return 1;
    }

    private int SetPotential(int x, int y, int k, int c, int level) {
        upd[x, y] = false;
        bridge[x, y, k] = 0;
        if (GetColor(x, y) == -c) return 0;

        int activeColor = (GameManager.instance.player1Turn ? 1 : -1);
        int b = (c == activeColor ? 66 : 52);

        float[] v = {
            GetPotential(x + 1, y, k, c),
            GetPotential(x, y + 1, k, c),
            GetPotential(x - 1, y + 1, k, c),
            GetPotential(x - 1, y, k, c),
            GetPotential(x, y - 1, k, c),
            GetPotential(x + 1, y - 1, k, c)
        };

        int db = 0;
        for (int i = 0; i < 6; i++) {
            if (v[i] >= 3e4f && v[(i + 2) % 6] >= 3e4f) {
                if (v[(i + 1) % 6] < 0) db = 32;
                else v[(i + 1) % 6] += 128;
            }
        }
        for (int i = 0; i < 6; i++) {
            if (v[i] >= 3e4f && v[(i + 3) % 6] >= 3e4f) {
                db += 30;
            }
        }

        int[] t = {1, 1, 1, 1, 1, 1};
        float m = 3e4f;
        for (int i = 0; i < 6; i++) {
            if (v[i] < 0) {
                v[i] += 3e4f;
                t[i] = 10;
            }
            if (m > v[i]) m = v[i];
        }

        int n = 0;
        for (int i = 0; i < 6; i++) {
            if (v[i] == m) n += t[i];
        }

        if (level > 1) {
            bridge[x, y, k] = n / 5;
            if (n >= 2 && n < 10) {
                bridge[x, y, k] = b + n - 2;
                m -= 32;
            }
            if (n < 2) {
                float o = 3e4f;
                for (int i = 0; i < 6; i++) {
                    if (v[i] > m && o > v[i]) o = v[i];
                }
                if (o <= m + 104) {
                    bridge[x, y, k] = b - (o - m) / 4f;
                    m -= 64;
                }
                m += o;
                m /= 2f;
            }
        }

        if (x > 0 && x < SZ - 1 && y > 0 && y < SZ - 1)
            bridge[x, y, k] += db;
        else bridge[x, y, k] -= 2;
        if ((x == 0 || x == SZ - 1) && (y == 0 || y == SZ - 1))
            bridge[x, y, k] /= 2;
        if (bridge[x, y, k] > 68) bridge[x, y, k] = 68;

        if (GetColor(x, y) == c) {
            if (m < potential[x, y, k]) {
                potential[x, y, k] = m;
                SetUpd(x + 1, y);
                SetUpd(x, y + 1);
                SetUpd(x - 1, y + 1);
                SetUpd(x - 1, y);
                SetUpd(x, y - 1);
                SetUpd(x + 1, y - 1);
                return 1;
            }
            return 0;
        }
        float d = 140;
        if (m + d < potential[x, y, k]) {
            potential[x, y, k] = m + d;
            SetUpd(x + 1, y);
            SetUpd(x, y + 1);
            SetUpd(x - 1, y + 1);
            SetUpd(x - 1, y);
            SetUpd(x, y - 1);
            SetUpd(x + 1, y - 1);
            return 1;
        }
        return 0;
    }

    public void UpdatePotentials(int level) {
        int moveCnt = GameManager.instance.moves;

        for (int x = 0; x < SZ; x++) {
            for (int y = 0; y < SZ; y++) {
                for (int k = 0; k < 4; k++) {
                    potential[x, y, k] = 2e4f;
                    bridge[x, y, k] = 0;
                }
            }
        }

        float d = 128f;
        for (int y = 0; y < SZ; y++) {
            // Player 1: left and right borders
            if (GetColor(0, y) == 0) potential[0, y, 0] = d;
            else if (GetColor(0, y) > 0) potential[0, y, 0] = 0;

            if (GetColor(SZ - 1, y) == 0) potential[SZ - 1, y, 1] = d;
            else if (GetColor(SZ - 1, y) > 0) potential[SZ - 1, y, 1] = 0;
        }
        for (int x = 0; x < SZ; x++) {
            // Player 2: top and bottom borders
            if (GetColor(x, 0) == 0) potential[x, 0, 2] = d;
            else if (GetColor(x, 0) < 0) potential[x, 0, 2] = 0;

            if (GetColor(x, SZ - 1) == 0) potential[x, SZ - 1, 3] = d;
            else if (GetColor(x, SZ - 1) < 0) potential[x, SZ - 1, 3] = 0;
        }

        for (int k = 0; k < 2; k++) {
            // Player 1 potential
            for (int x = 0; x < SZ; x++) {
                for (int y = 0; y < SZ; y++)
                    upd[x, y] = true;
            }
            int n = 0;
            int b;
            do {
                n++;
                b = 0;
                for (int x = 0; x < SZ; x++) {
                    for (int y = 0; y < SZ; y++) {
                        if (upd[x, y]) b += SetPotential(x, y, k, 1, level);
                    }
                }
                for (int x = SZ - 1; x >= 0; x--) {
                    for (int y = SZ - 1; y >= 0; y--) {
                        if (upd[x, y]) b += SetPotential(x, y, k, 1, level);
                    }
                }
            } while (b > 0 && n < 12);
        }
        for (int k = 2; k < 4; k++) {
            // Player 2 potential
            for (int x = 0; x < SZ; x++) {
                for (int y = 0; y < SZ; y++)
                    upd[x, y] = true;
            }
            int n = 0;
            int b;
            do {
                n++;
                b = 0;
                for (int x = 0; x < SZ; x++) {
                    for (int y = 0; y < SZ; y++) {
                        if (upd[x, y]) b += SetPotential(x, y, k, -1, level);
                    }
                }
                for (int x = SZ - 1; x >= 0; x--) {
                    for (int y = SZ - 1; y >= 0; y--) {
                        if (upd[x, y]) b += SetPotential(x, y, k, -1, level);
                    }
                }
            } while (b > 0 && n < 12);
        }
    }

    private bool TryToSwap() {
        int moveCnt = GameManager.instance.moves;
        if (moveCnt == 0) {
            int x = UnityEngine.Random.Range(0, 4);
            int y = UnityEngine.Random.Range(0, 4 - x);
            if (UnityEngine.Random.value < .5f) {
                x = SZ - 1 - x;
                y = SZ - 1 - y;
            }
            GameManager.instance.HandleFlip(x, y);
            return true;
        }
        if (moveCnt == 1) {
            for (int x = 0; x < SZ; x++) {
                for (int y = 0; y < SZ; y++) {
                    if (GetColor(x, y) != 0) {
                        if (x + y < 2 || x + y > 2 * SZ - 4) return false;
                        if (x + y == 2 || x + y == 2 * SZ - 4) {
                            if (UnityEngine.Random.value < .5f) return false;
                        }
                        GameManager.instance.HandleSwapRule();
                        return true;
                    }
                }
            }
        }
        return false;
    }

    public void MakeMove(int color, int level) {
        if (TryToSwap()) return;

        UpdatePotentials(level);

        // for (int x = 0; x < SZ; x++) {
        //     string s = "";
        //     for (int y = 0; y < SZ; y++) s += potential[x, y, 0] + " ";
        //     Debug.Log(s);
        // }

        int moveCnt = GameManager.instance.moves;
        float f = (moveCnt > 0 ? 190f / (moveCnt * moveCnt) : 0f);

        int xQ = 0;
        int yQ = 0;
        for (int x = 0; x < SZ; x++) {
            for (int y = 0; y < SZ; y++) {
                if (GetColor(x, y) != 0) {
                    xQ += 2 * x + 1 - SZ;
                    yQ += 2 * y + 1 - SZ;
                }
            }
        }
        xQ = Math.Sign(xQ);
        yQ = Math.Sign(yQ);

        float[] v = new float[SZ * SZ];
        float m = 2e4f;
        int xB = 0;
        int yB = 0;
        for (int x = 0; x < SZ; x++) {
            for (int y = 0; y < SZ; y++) {
                if (GetColor(x, y) == 0) {
                    float mp = UnityEngine.Random.value * (49 - level * 16);
                    mp += (Math.Abs(x - 5) + Math.Abs(y - 5)) * f;
                    mp += (8f * (xQ * (x - 5) + yQ * (y - 5))) / (moveCnt + 1f);

                    if (level > 2) {
                        for (int i = 0; i < 4; i++) mp -= bridge[x, y, i];
                    }

                    float p0 = potential[x, y, 0] + potential[x, y, 1];
                    float p1 = potential[x, y, 2] + potential[x, y, 3];
                    mp += p0 + p1;
                    if (p0 <= 268 || p1 <= 268) mp -= 400;

                    v[GameManager.Normalize(x, y)] = mp;
                    if (mp < m) {
                        m = mp;
                        xB = x;
                        yB = y;
                    }
                }
            }
        }

        if (level > 2) {
            m += 108;
            for (int x = 0; x < SZ; x++) {
                for (int y = 0; y < SZ; y++) {
                    int currNorm = GameManager.Normalize(x, y);
                    if (v[currNorm] < m) {
                        if (color < 0) { // Player 2
                            if (x > 3 && x < SZ - 1 && y > 0 && y < 3) {
                                if (GetColor(x - 1, y + 2) == -color) {
                                    int connect = CanConnectFarBorder(x - 1, y + 2, -color);
                                    if (connect < 2) {
                                        xB = x;
                                        if (connect < -1) {
                                            xB--;
                                            connect++;
                                        }
                                        yB = y - connect;
                                        m = v[currNorm];
                                    }
                                }
                            }
                            if (x > 0 && x < SZ - 1 && y == 0) {
                                if (
                                    GetColor(x - 1, y + 2) == -color &&
                                    GetColor(x - 1, y) == 0 &&
                                    GetColor(x - 1, y + 1) == 0 &&
                                    GetColor(x, y + 1) == 0 &&
                                    GetColor(x + 1, y) == 0
                                ) {
                                    xB = x;
                                    yB = y;
                                    m = v[currNorm];
                                }
                            }
                            if (x > 0 && x < SZ - 4 && y < SZ - 1 && y > SZ - 4) {
                                if (GetColor(x + 1, y - 2) == -color) {
                                    int connect = CanConnectFarBorder(x + 1, y - 2, -color);
                                    if (connect < 2) {
                                        xB = x;
                                        if (connect < -1) {
                                            xB++;
                                            connect++;
                                        }
                                        yB = y + connect;
                                        m = v[currNorm];
                                    }
                                }
                            }
                            if (x > 0 && x < SZ - 1 && y == SZ - 1) {
                                if (
                                    GetColor(x + 1, y - 2) == -color &&
                                    GetColor(x + 1, y) == 0 &&
                                    GetColor(x + 1, y - 1) == 0 &&
                                    GetColor(x, y - 1) == 0 &&
                                    GetColor(x - 1, y) == 0
                                ) {
                                    xB = x;
                                    yB = y;
                                    m = v[currNorm];
                                }
                            }
                        } else {
                            if (y > 3 && y < SZ - 1 && x > 0 && x < 3) {
                                if (GetColor(x + 2, y - 1) == -color) {
                                    int connect = CanConnectFarBorder(x + 2, y - 1, -color);
                                    if (connect < 2) {
                                        yB = y;
                                        if (connect < -1) {
                                            yB--;
                                            connect++;
                                        }
                                        xB = x - connect;
                                        m = v[currNorm];
                                    }
                                }
                            }
                            if (y > 0 && y < SZ - 1 && x == 0) {
                                if (
                                    GetColor(x + 2, y - 1) == -color &&
                                    GetColor(x, y - 1) == 0 &&
                                    GetColor(x + 1, y - 1) == 0 &&
                                    GetColor(x + 1, y) == 0 &&
                                    GetColor(x, y + 1) == 0
                                ) {
                                    xB = x;
                                    yB = y;
                                    m = v[currNorm];
                                }
                            }
                            if (y > 0 && y < SZ - 4 && x < SZ - 1 && x > SZ - 4) {
                                if (GetColor(x - 2, y + 1) == -color) {
                                    int connect = CanConnectFarBorder(x - 2, y + 1, -color);
                                    if (connect < 2) {
                                        yB = y;
                                        if (connect < -1) {
                                            yB++;
                                            connect++;
                                        }
                                        xB = x + connect;
                                        m = v[currNorm];
                                    }
                                }
                            }
                            if (y > 0 && y < SZ - 1 && x == SZ - 1) {
                                if (
                                    GetColor(x - 2, y + 1) == -color &&
                                    GetColor(x, y + 1) == 0 &&
                                    GetColor(x - 1, y + 1) == 0 &&
                                    GetColor(x - 1, y) == 0 &&
                                    GetColor(x, y - 1) == 0
                                ) {
                                    xB = x;
                                    yB = y;
                                    m = v[currNorm];
                                }
                            }
                        }
                    }
                }
            }
        }
        GameManager.instance.HandleFlip(xB, yB);
    }
}