function count = zero_crossings(x)
% Count the number of zero-crossings from the supplied time-domain
% input vector.  A simple method is applied here that can be easily
% ported to a real-time system that would minimize the number of
% if-else conditionals.
%
% Usage:     COUNT = zero_crossings(X);
%
%            X     is the input time-domain signal (one dimensional)
%            COUNT is the amount of zero-crossings in the input signal
%
% Author:    sparafucile17 06/27/04
%

% initial value
count = 0;

% error checks
if(length(x) == 1)
    error('ERROR: input signal must have more than one element');
end

if((size(x, 2) ~= 1) && (size(x, 1) ~= 1))
    error('ERROR: Input must be one-dimensional');
end
    
% force signal to be a vector oriented in the same direction
x = x(:);

num_samples = length(x);
for i=2:num_samples

    % Any time you multiply to adjacent values that have a sign difference
    % the result will always be negative.  When the signs are identical,
    % the product will always be positive.
    if((x(i) * x(i-1)) < 0)
        count = count + 1;
    end
    
end