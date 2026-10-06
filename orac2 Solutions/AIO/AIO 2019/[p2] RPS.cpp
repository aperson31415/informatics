 #include <bits/stdc++.h>
using namespace std;
 
int main() {
    int N, Ra, Pa, Sa, Rb, Pb, Sb;
    int points = 0, current_data;
    cin >> N >> Ra >> Pa >> Sa >> Rb >> Pb >> Sb;
 
    // Do a systematic try all wins, try all draws, try all losses
    // Oops should've used a function to shorten this code but already too far through :(
 
    current_data = min(Sb, Pa); // This is trying to win with Scissors
    points += current_data; Sb -= current_data; Pa -= current_data;
 
    current_data = min(Pb, Ra); // This is trying to witn with Paper
    points += current_data; Pb -= current_data; Ra -= current_data;
 
    current_data = min(Rb, Sa); // This is trying to win with Rock
    points += current_data; Rb -= current_data; Sa -= current_data;
 
    current_data = min(Sb, Sa); // This is trying to draw with Scissors
    Sb -= current_data; Sa -= current_data;
 
    current_data = min(Pb, Pa); // This is trying to draw with Paper
    Pb -= current_data; Pa -= current_data;
 
    current_data = min(Rb, Ra); // This is trying to draw with Rock
    Rb -= current_data; Ra -= current_data;
 
    // Now just manually calculate losses, cuz everything left over is losses
    points -= (Rb + Pb + Sb);
 
    cout << points;
}
