function [k] = fit(x, y)

cof = [sum(x.^10), sum(x.^9), sum(x.^8), sum(x.^7), sum(x.^6), sum(x.^5), sum(x.^4), sum(x.^3), sum(x.^2), sum(x)];

n = length(x);

A = [cof(1), cof(2), cof(3), cof(4), cof(5), cof(6); 
     cof(2), cof(3), cof(4), cof(5), cof(6), cof(7); 
     cof(3), cof(4), cof(5), cof(6), cof(7), cof(8);
     cof(4), cof(5), cof(6), cof(7), cof(8), cof(9);
     cof(5), cof(6), cof(7), cof(8), cof(9), cof(10);
     cof(6), cof(7), cof(8), cof(9), cof(10), n];

B = [sum((x.^5) .* y); sum((x.^4) .* y); sum((x.^3) .* y); sum((x.^2) .* y); sum(x .* y); sum(y)];

cof_p = A\B;

k = cof_p(1) * x.^5 + cof_p(2) * x.^4 + cof_p(3) * x.^3 + cof_p(4) * x.^2 + cof_p(5) * x.^1 + cof_p(6);

end

