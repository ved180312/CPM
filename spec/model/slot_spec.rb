require 'rails_helper'

RSpec.describe Slot, type: :model do
    subject { Slot.new(slot_number: 1, floor_id: 1)}
    before {subject.save}

    it 'Slot Number Should Be Present' do
      subject.slot_number = nil
      expect(subject).to_not be_valid
    end

    it 'Floor Id Should Be Present' do
      subject.floor_id = nil
      expect(subject).to_not be_valid
    end 
end