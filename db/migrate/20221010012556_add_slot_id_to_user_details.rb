class AddSlotIdToUserDetails < ActiveRecord::Migration[7.0]
  def change
    add_column :user_details, :slot_id, :integer
  end
end
