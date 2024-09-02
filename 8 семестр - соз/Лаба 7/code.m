% Определение функции
%f = @(x1, x2) x1.^2 .* sin(x2 - 5);
f = @(x1, x2) 2 * x1.^2 .* sin(x2 + 3) .* cos(x2 - 3);
% Построение графиков с разными шагами для диапазона x
figure;

% График с шагом 0.01
subplot(3, 1, 1);
x1_range = -6:0.01:5;
x2_range = -6:0.01:4;
[x1, x2] = meshgrid(x1_range, x2_range);
y = f(x1, x2);
surf(x1, x2, y, 'EdgeColor','none');
title('Шаг 0.01');

% График с шагом 0.05
subplot(3, 1, 2);
x1_range = -6:0.05:5;
x2_range = -6:0.05:4;
[x1, x2] = meshgrid(x1_range, x2_range);
y = f(x1, x2);
surf(x1, x2, y, 'EdgeColor','none');
title('Шаг 0.05');

% График с шагом 0.1
subplot(3, 1, 3);
x1_range = -6:0.1:5;
x2_range = -6:0.1:4;
[x1, x2] = meshgrid(x1_range, x2_range);
y = f(x1, x2);
surf(x1, x2, y, 'EdgeColor','none');
title('Шаг 0.1');

% Настройка общих свойств графиков
for i = 1:3
    subplot(3, 1, i);
    xlabel('x1');
    ylabel('x2');
    zlabel('y');
    grid on;
end
