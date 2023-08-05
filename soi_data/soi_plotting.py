import matplotlib.pyplot as plt
import numpy as np


# +++ Exercise 2: average of the expected number of infected people depending on 'p1' +++

# processing of the data
soi_avg_ratio_infected_over_p1_03_03 = np.loadtxt("soi_average_ratio_infected_over_p1_a.csv", delimiter = ",", skiprows = 0)
soi_avg_ratio_infected_over_p1_06_03 = np.loadtxt("soi_average_ratio_infected_over_p1_b.csv", delimiter = ",", skiprows = 0)
soi_avg_ratio_infected_over_p1_03_06 = np.loadtxt("soi_average_ratio_infected_over_p1_c.csv", delimiter = ",", skiprows = 0)
p1_array = soi_avg_ratio_infected_over_p1_03_03[0,1:]
# p2 = 0.3, p3 = 0.3
avg_ratio_infected_p1_03_03_L16 = soi_avg_ratio_infected_over_p1_03_03[1,1:]
avg_ratio_infected_p1_03_03_L32 = soi_avg_ratio_infected_over_p1_03_03[2,1:]
avg_ratio_infected_p1_03_03_L64 = soi_avg_ratio_infected_over_p1_03_03[3,1:]
avg_ratio_infected_p1_03_03_L128 = soi_avg_ratio_infected_over_p1_03_03[4,1:]
# p2 = 0.6, p3 = 0.3
avg_ratio_infected_p1_06_03_L16 = soi_avg_ratio_infected_over_p1_06_03[1,1:]
avg_ratio_infected_p1_06_03_L32 = soi_avg_ratio_infected_over_p1_06_03[2,1:]
avg_ratio_infected_p1_06_03_L64 = soi_avg_ratio_infected_over_p1_06_03[3,1:]
avg_ratio_infected_p1_06_03_L128 = soi_avg_ratio_infected_over_p1_06_03[4,1:]
# p2 = 0.3, p3 = 0.6
avg_ratio_infected_p1_03_06_L16 = soi_avg_ratio_infected_over_p1_03_06[1,1:]
avg_ratio_infected_p1_03_06_L32 = soi_avg_ratio_infected_over_p1_03_06[2,1:]
avg_ratio_infected_p1_03_06_L64 = soi_avg_ratio_infected_over_p1_03_06[3,1:]
avg_ratio_infected_p1_03_06_L128 = soi_avg_ratio_infected_over_p1_03_06[4,1:]


# plotting of the data
fig, ax = plt.subplots(3, figsize=(12.5, 17))

ax[0].set_xlabel(r'turnover probability $p_1\,(S\rightarrow I\,)$')
ax[0].set_ylabel(r'avg. infection rate $\overline{\langle I\rangle}$')
ax[0].grid()
ax[0].grid(which='minor', color = '#999999', alpha = 0.2, linestyle = '-')
ax[0].minorticks_on()
ax[0].scatter(p1_array, avg_ratio_infected_p1_03_03_L16, color = 'blue', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=16$')
ax[0].scatter(p1_array, avg_ratio_infected_p1_03_03_L32, color = 'xkcd:red pink', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=32$')
ax[0].scatter(p1_array, avg_ratio_infected_p1_03_03_L64, color = 'xkcd:lightish blue', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=64$')
ax[0].scatter(p1_array, avg_ratio_infected_p1_03_03_L128, color = 'black', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=128$')
ax[0].plot(p1_array, avg_ratio_infected_p1_03_03_L16, color = 'blue', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[0].plot(p1_array, avg_ratio_infected_p1_03_03_L32, color = 'xkcd:red pink', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[0].plot(p1_array, avg_ratio_infected_p1_03_03_L64, color = 'xkcd:lightish blue', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[0].plot(p1_array, avg_ratio_infected_p1_03_03_L128, color = 'black', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[0].set_title(r'$\overline{\langle I\rangle}$ over $p_1$ for $T=1000$ with $p_2=0.3$, $p_3=0.3$')
ax[0].legend()
ax[0].legend(loc = "upper left")
ax[0].set_ylim([-0.02, 0.6])

ax[1].set_xlabel(r'turnover probability $p_1\,(S\rightarrow I\,)$')
ax[1].set_ylabel(r'avg. infection rate $\overline{\langle I\rangle}$')
ax[1].grid()
ax[1].grid(which='minor', color = '#999999', alpha = 0.2, linestyle = '-')
ax[1].minorticks_on()
ax[1].scatter(p1_array, avg_ratio_infected_p1_06_03_L16, color = 'blue', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=16$')
ax[1].scatter(p1_array, avg_ratio_infected_p1_06_03_L32, color = 'xkcd:red pink', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=32$')
ax[1].scatter(p1_array, avg_ratio_infected_p1_06_03_L64, color = 'xkcd:lightish blue', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=64$')
ax[1].scatter(p1_array, avg_ratio_infected_p1_06_03_L128, color = 'black', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=128$')
ax[1].plot(p1_array, avg_ratio_infected_p1_06_03_L16, color = 'blue', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[1].plot(p1_array, avg_ratio_infected_p1_06_03_L32, color = 'xkcd:red pink', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[1].plot(p1_array, avg_ratio_infected_p1_06_03_L64, color = 'xkcd:lightish blue', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[1].plot(p1_array, avg_ratio_infected_p1_06_03_L128, color = 'black', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[1].set_title(r'$\overline{\langle I\rangle}$ over $p_1$ for $T=1000$ with $p_2=0.6$, $p_3=0.3$')
ax[1].legend()
ax[1].legend(loc = "upper left")
ax[1].set_ylim([-0.02, 0.6])

ax[2].set_xlabel(r'turnover probability $p_1\,(S\rightarrow I\,)$')
ax[2].set_ylabel(r'avg. infection rate $\overline{\langle I\rangle}$')
ax[2].grid()
ax[2].grid(which='minor', color = '#999999', alpha = 0.2, linestyle = '-')
ax[2].minorticks_on()
ax[2].scatter(p1_array, avg_ratio_infected_p1_03_06_L16, color = 'blue', s = 10, alpha = 0.5, linewidth = 1, linestyle = '--', label = r'$L=16$')
ax[2].scatter(p1_array, avg_ratio_infected_p1_03_06_L32, color = 'xkcd:red pink', s = 10, alpha = 0.5, linewidth = 1, linestyle = '--', label = r'$L=32$')
ax[2].scatter(p1_array, avg_ratio_infected_p1_03_06_L64, color = 'xkcd:lightish blue', s = 10, alpha = 0.5, linewidth = 1, linestyle = '--', label = r'$L=64$')
ax[2].scatter(p1_array, avg_ratio_infected_p1_03_06_L128, color = 'black', s = 10, alpha = 0.5, linewidth = 1, linestyle = '--', label = r'$L=128$')
ax[2].plot(p1_array, avg_ratio_infected_p1_03_06_L16, color = 'blue', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[2].plot(p1_array, avg_ratio_infected_p1_03_06_L32, color = 'xkcd:red pink', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[2].plot(p1_array, avg_ratio_infected_p1_03_06_L64, color = 'xkcd:lightish blue', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[2].plot(p1_array, avg_ratio_infected_p1_03_06_L128, color = 'black', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[2].set_title(r'$\overline{\langle I\rangle}$ over $p_1$ for $T=1000$ with $p_2=0.3$, $p_3=0.6$')
ax[2].legend()
ax[2].legend(loc = "upper left")
ax[2].set_ylim([-0.02, 0.6])

plt.savefig('visualizations/soi_average_infected_over_p1.pdf', facecolor = 'white', bbox_inches='tight')
plt.savefig('../soi_pdf/images/soi_average_infected_over_p1.pgf', facecolor = 'white', bbox_inches='tight')


# refined plot for L = 128
fig, ax = plt.subplots(1, 2, figsize=(12.5, 5.5))

ax[0].set_xlabel(r'turnover probability $p_1\,(S\rightarrow I\,)$')
ax[0].set_ylabel(r'avg. infection rate $\overline{\langle I\rangle}$')
ax[0].grid()
ax[0].grid(which='minor', color = '#999999', alpha = 0.2, linestyle = '-')
ax[0].minorticks_on()
ax[0].scatter(p1_array, avg_ratio_infected_p1_03_03_L128, color = 'xkcd:red pink', s = 10, alpha = 0.5, linewidth = 1, label = r'$p_2=0.3$, $p_3=0.3$')
ax[0].scatter(p1_array, avg_ratio_infected_p1_06_03_L128, color = 'blue', s = 10, alpha = 0.5, linewidth = 1, label = r'$p_2=0.6$, $p_3=0.3$')
ax[0].scatter(p1_array, avg_ratio_infected_p1_03_06_L128, color = 'black', s = 10, alpha = 0.5, linewidth = 1, label = r'$p_2=0.3$, $p_3=0.6$')
ax[0].plot(p1_array, avg_ratio_infected_p1_03_03_L128, color = 'xkcd:red pink', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[0].plot(p1_array, avg_ratio_infected_p1_06_03_L128, color = 'blue', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[0].plot(p1_array, avg_ratio_infected_p1_03_06_L128, color = 'black', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[0].set_title(r'$\overline{\langle I\rangle}$ over $p_1$ for $T=1000$ for $L=128$')
ax[0].legend()
ax[0].legend(loc = "upper left")
ax[0].set_ylim([-0.02, 0.6])

ax[1].set_xlabel(r'turnover probability $p_1\,(S\rightarrow I\,)$')
ax[1].set_ylabel(r'avg. infection rate $\overline{\langle I\rangle}$')
ax[1].grid()
ax[1].grid(which='minor', color = '#999999', alpha = 0.2, linestyle = '-')
ax[1].minorticks_on()
ax[1].scatter(p1_array, avg_ratio_infected_p1_03_03_L128, color = 'xkcd:red pink', s = 10, alpha = 0.5, linewidth = 1, label = r'$p_2=0.3$, $p_3=0.3$')
ax[1].scatter(p1_array, avg_ratio_infected_p1_06_03_L128, color = 'blue', s = 10, alpha = 0.5, linewidth = 1, label = r'$p_2=0.6$, $p_3=0.3$')
ax[1].scatter(p1_array, avg_ratio_infected_p1_03_06_L128, color = 'black', s = 10, alpha = 0.5, linewidth = 1, label = r'$p_2=0.3$, $p_3=0.6$')
ax[1].plot(p1_array, avg_ratio_infected_p1_03_03_L128, color = 'xkcd:red pink', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[1].plot(p1_array, avg_ratio_infected_p1_06_03_L128, color = 'blue', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[1].plot(p1_array, avg_ratio_infected_p1_03_06_L128, color = 'black', alpha = 0.5, linewidth = 1, linestyle = '--')
ax[1].set_title(r'$\overline{\langle I\rangle}$ over $p_1$ for $T=1000$ for $L=128$')
ax[1].legend()
ax[1].legend(loc = "upper left")
ax[1].set_xlim([-0.01, 0.5])
ax[1].set_ylim([-0.01, 0.1])

plt.savefig('visualizations/soi_average_infected_over_p1_L128.pdf', facecolor = 'white', bbox_inches='tight')
plt.savefig('../soi_pdf/images/soi_average_infected_over_p1_L128.pgf', facecolor = 'white', bbox_inches='tight')


# +++ Exercise 3: average of the expected number of infected people depending on 'p4' +++

# processing of the data
soi_avg_ratio_infected_over_p4 = np.loadtxt("soi_average_ratio_infected_over_p4_v.csv", delimiter = ",", skiprows = 0)
p4_array = soi_avg_ratio_infected_over_p4[0,1:]
avg_ratio_infected_p4_L16 = soi_avg_ratio_infected_over_p4[1,1:]
avg_ratio_infected_p4_L32 = soi_avg_ratio_infected_over_p4[2,1:]
avg_ratio_infected_p4_L64 = soi_avg_ratio_infected_over_p4[3,1:]
avg_ratio_infected_p4_L128 = soi_avg_ratio_infected_over_p4[4,1:]


# plotting of the data
fig, ax = plt.subplots(figsize=(12.5, 5.5))

ax.set_xlabel(r'probability $p_4$ of a vaccinated person $V$ occupying a grid node')
ax.set_ylabel(r'avg. infection rate $\overline{\langle I\rangle}$')
ax.grid()
ax.grid(which='minor', color = '#999999', alpha = 0.2, linestyle = '-')
ax.minorticks_on()
ax.scatter(p4_array, avg_ratio_infected_p4_L16, color = 'blue', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=16$')
ax.scatter(p4_array, avg_ratio_infected_p4_L32, color = 'xkcd:red pink', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=32$')
ax.scatter(p4_array, avg_ratio_infected_p4_L64, color = 'xkcd:lightish blue', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=64$')
ax.scatter(p4_array, avg_ratio_infected_p4_L128, color = 'black', s = 10, alpha = 0.5, linewidth = 1, label = r'$L=128$')
ax.plot(p4_array, avg_ratio_infected_p4_L16, color = 'blue', alpha = 0.5, linewidth = 1, linestyle = '--')
ax.plot(p4_array, avg_ratio_infected_p4_L32, color = 'xkcd:red pink', alpha = 0.5, linewidth = 1, linestyle = '--')
ax.plot(p4_array, avg_ratio_infected_p4_L64, color = 'xkcd:lightish blue', alpha = 0.5, linewidth = 1, linestyle = '--')
ax.plot(p4_array, avg_ratio_infected_p4_L128, color = 'black', alpha = 0.5, linewidth = 1, linestyle = '--')
ax.set_title(r'$\overline{\langle I\rangle}$ over $p_4$ for $T=1000$ with $p_1=p_2=p_3=0.5$')
ax.legend()
ax.legend(loc = "upper right")

plt.savefig('visualizations/soi_average_infected_over_p4.pdf', facecolor = 'white', bbox_inches='tight')
plt.savefig('../soi_pdf/images/soi_average_infected_over_p4.pgf', facecolor = 'white', bbox_inches='tight')


# +++ Time Analysis: time development of the infection rate over N samples +++

# processing of the data
soi_ratio_over_time = np.loadtxt("soi_ratio_over_time.csv", delimiter = ",", skiprows = 0)
time_array = soi_ratio_over_time[0,1:]
mean_array = soi_ratio_over_time[-2,1:]
sigma_array = soi_ratio_over_time[-1,1:]

# plotting of the data
fig, ax = plt.subplots(figsize=(12.5, 5.5))

ax.set_xlabel(r'time step $t$')
ax.set_ylabel(r'infection rate $\langle I\rangle_t$')
ax.grid()
ax.grid(which='minor', color = '#999999', alpha = 0.2, linestyle = '-')
ax.minorticks_on()
ax.plot(time_array, soi_ratio_over_time[2,1:], color = 'grey', alpha = 0.25, linewidth = 0.5, label = r'individual samples $\langle I\rangle_t$')
for ratio_over_time in soi_ratio_over_time[2:-2,1:]:
    ax.plot(time_array, ratio_over_time, color = 'grey', alpha = 0.25, linewidth = 0.5)
ax.plot(time_array, mean_array, color = 'black', alpha = 0.75, linewidth = 1, label = r'mean $\overline{\langle I\rangle_t}$')
ax.fill_between(time_array, mean_array-sigma_array, mean_array+sigma_array, color = 'xkcd:red pink', alpha = 0.2, linewidth = 1, label = r'standard deviation $\sigma_{\langle I\rangle_t}$')
ax.set_title(r'time evolution of $\langle I\rangle_t$ for $T=1000$ simulation steps and $L=64$ with $p_1=p_2=p_3=0.5$')
ax.legend()
ax.legend(loc = "upper right")

plt.savefig('visualizations/soi_infected_over_time.pdf', facecolor = 'white', bbox_inches='tight')
plt.savefig('../soi_pdf/images/soi_infected_over_time.pgf', facecolor = 'white', bbox_inches='tight')