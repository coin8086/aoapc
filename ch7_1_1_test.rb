#!/usr/bin/env ruby

require_relative 'test_helper'

def gen_exprs
  exprs = Array.new(80) {|i| []}
  a = '0123456789'.split ''
  a.permutation do |p|
    enu = p.slice(0, 5).join #enumerator
    den = p.slice(5, 5).join #denominator
    e = enu.to_i
    d = den.to_i
    if e % d == 0
      exprs[e / d].push [enu, den]
    end
  end
  (2..79).each do |i|
    exprs[i].sort_by! {|e| e[1]} #sort by denominator
  end
  exprs
end

test_file = File.expand_path(__FILE__)
test(test_file) do |input, output|
  exprs = gen_exprs
  input = File.open(input, 'wb')
  output = File.open(output, 'wb')
  (2..79).each do |i|
    input.puts i
    if exprs[i].empty?
      output.puts "Impossible."
    else
      exprs[i].each do |e|
        output.puts "#{e[0]} / #{e[1]} = #{i}"
      end
    end
    output.puts
  end
  input.close
  output.close
end

