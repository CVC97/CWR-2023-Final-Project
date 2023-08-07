\LoadClass[12pt, titlepage, a4paper]{article}

%******************************Commands*******************************

\newcommand{\infd}[1][]{\,\text{d}{#1}}
\newcommand{\tdiv}[1]{\text{div}\,\Vec{#1}}
\newcommand{\tgrad}[1]{\text{grad}\,{#1}}

\newcommand{\pmnum}[3]{\ensuremath{({#1}\,\pm\,{#2})\,\si{#3}}}
\newcommand{\BVec}[1]{\boldsymbol{\mathrm{#1}}}

% state of the grid nodes
\newcommand{\susceptible}{\textit{S}}
\newcommand{\infected}{\textit{I}}
\newcommand{\recovered}{\textit{R}}
\newcommand{\vaccinated}{\textit{V}}

% tikz macros

    
\newcommand{\R}{2cm} % Circle radius
% \newcommand{\texta}{\textbf{S} \\ Susceptible}
% \newcommand{\textb}{\textbf{I} \\ Infected}
% \newcommand{\textc}{\textbf{R} \\ Recovered}
\newcommand{\texta}{\susceptible \\ Susceptible}
\newcommand{\textb}{\infected \\ Infected}
\newcommand{\textc}{\recovered \\ Recovered}